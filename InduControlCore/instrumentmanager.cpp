#include "instrumentmanager.h"
#include <QDebug>
#include <QRandomGenerator>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "../Instruments/ppmssimulation.h"

InstrumentManager::InstrumentManager()
    : timer_(new QTimer(this))
    , ppmssimu_(std::make_shared<PpmsSimulation>())
{
    connect(timer_, &QTimer::timeout, this, &InstrumentManager::onPolling);
    timer_->start(200);
}

void InstrumentManager::setTempSetpoint(double setpoint, double rate)
{
    ppmssimu_->setTempSetpoint(setpoint, rate);
}


void InstrumentManager::onPolling()
{
    auto dataPoint = ppmssimu_->generateVariablesTc();
    emit newData(dataPoint);
}
