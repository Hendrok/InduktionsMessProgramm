#include "instrumentmanager.h"
#include <QDebug>
#include <QRandomGenerator>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "../Instruments/ppmssimulation.h"
#include "../Instruments/lockinsimulation.h"

/* FIXME
 * - #include <QRandomGenerator> ist unnötig
 * - #include "../InduCore/datapoint.h" ist unnötig
 *   (wird schon in der Header-Datei includiert)
 * - Zwischen Methode SetinputVoltage und onPolling
 *   ist eine Leerzeile zu viel
 * - in onPolling ist ein Leerzeichen bei make_shared zu viel
 */

InstrumentManager::InstrumentManager()
    : timer_(new QTimer(this))
    , ppmssimu_(std::make_shared<PpmsSimulation>())
    , lockinsimu_(std::make_shared<LockInSimulation>())
{
    connect(timer_, &QTimer::timeout, this, &InstrumentManager::onPolling);
    timer_->start(200);
}

void InstrumentManager::setTempSetpoint(double setpoint, double rate)
{
    ppmssimu_->setTempSetpoint(setpoint, rate);
}

void InstrumentManager::SetInputVoltage(double InputVoltage)
{
    lockinsimu_->SetInputVoltage(InputVoltage);
}


void InstrumentManager::onPolling()
{
    DataPoint dataPoint;

    dataPoint.setPpmsdata(std::make_shared<const PpmsDataPoint> (ppmssimu_->generateVariables()));
    dataPoint.setLockindata(std::make_shared<const LockInDataPoint> (lockinsimu_->lockInLogik()));

    auto dPoint = std::make_shared <DataPoint> (dataPoint);
    emit newData(dPoint);
}
