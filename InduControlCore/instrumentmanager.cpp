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
    connect(timer_, &QTimer::timeout,
            this, &InstrumentManager::onPolling);
    connect(ppmssimu_.get(), &PpmsSimulation::newTempSP,
            this, &InstrumentManager::newTempSP);
    connect(ppmssimu_.get(), &PpmsSimulation::newMagSP,
            this, &InstrumentManager::newMagSP);
    connect(ppmssimu_.get(), &PpmsSimulation::newAngleSP,
            this, &InstrumentManager::newAngleSP);
    connect(lockinsimu_.get(), &LockInSimulation::newFreqSP,
            this, &InstrumentManager::newFreqSP);
    connect(lockinsimu_.get(), &LockInSimulation::newSensivitySP,
            this, &InstrumentManager::newSensivitySP);
    connect(lockinsimu_.get(), &LockInSimulation::newHarmonicSP,
            this, &InstrumentManager::newHarmonicSP);

    timer_->start(200);
}

void InstrumentManager::setTempSetpoint(double setpoint, double rate)
{
    ppmssimu_->setTempSetpoint(setpoint, rate);
}

void InstrumentManager::setInputVoltage(double InputVoltage)
{
    lockinsimu_->setInputVoltage(InputVoltage);
}

void InstrumentManager::setMagFieldSP(double magField, double magRate)
{
    ppmssimu_->setMagField(magField, magRate);
}

void InstrumentManager::setAngle(double angle)
{
    ppmssimu_->setAngle(angle);
}

void InstrumentManager::setFrequency(double freq)
{
    lockinsimu_->setFreq(freq);
}

void InstrumentManager::setSensivity(double sensivity)
{
    lockinsimu_->setSensivity(sensivity);
}

void InstrumentManager::setHarmonic(double harmonic)
{
    lockinsimu_->setHarmonic(harmonic);
}



void InstrumentManager::onPolling()
{
    DataPoint dataPoint;

    dataPoint.setPpmsdata(std::make_shared<const PpmsDataPoint>(ppmssimu_->generateVariables()));
    dataPoint.setLockindata(std::make_shared<const LockInDataPoint>(lockinsimu_->lockInLogik()));

    auto dPoint = std::make_shared<DataPoint>(dataPoint);
    emit newData(dPoint);
}
