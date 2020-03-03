#include "instrumentmanager.h"
#include <QDebug>

//Internal Classes
#include "../Instruments/ppmssimulation.h"
#include "../Instruments/lockinsimulation.h"


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

void InstrumentManager::setInputVoltage(double InputVoltage)
{
    lockinsimu_->SetInputVoltage(InputVoltage);
}

void InstrumentManager::setPpmsVariables(double magField, double angle)
{
    ppmssimu_->setPpmsVariables(magField, angle);
}

void InstrumentManager::setLockVariables(double freq, double sensivity, int harmonicW)
{
    lockinsimu_->setLockVariables(freq, sensivity, harmonicW);
}

void InstrumentManager::onPolling()
{
    DataPoint dataPoint;

    dataPoint.setPpmsdata(std::make_shared<const PpmsDataPoint>(ppmssimu_->generateVariables()));
    dataPoint.setLockindata(std::make_shared<const LockInDataPoint>(lockinsimu_->lockInLogik()));

    auto dPoint = std::make_shared<DataPoint>(dataPoint);
    emit newData(dPoint);
}
