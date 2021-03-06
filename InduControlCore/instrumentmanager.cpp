#include "instrumentmanager.h"
#include <QDebug>
#include <QThread>
#include <QtConcurrent/QtConcurrent>

//Internal Classes
#include "../Instruments/ppmssimulation.h"
#include "../Instruments/lockinsimulation.h"
#include "../Instruments/ppmsabstract.h"
#include "../Instruments/lockinabstract.h"
#include "../Instruments/ppmsinstrument.h"
#include "../Instruments/lockinsr830.h"
#include "../Instruments/gpib.h"
#include "../Instruments/lockinsens.h"
const int PPMSADDRESS = 15;
//const int LOCKINADRESS = 10;

InstrumentManager::InstrumentManager()
    : timer_(new QTimer(this))
    , gpib_(std::make_shared<GPIB>())
    , lockinsens_(std::make_shared<LockInSens> ())
{
    connect(timer_, &QTimer::timeout,
            this, &InstrumentManager::onPolling);

    timer_->start(1000);

    if(simulation_ == 1)
    {
        ppms_ = new PpmsSimulation;
        lockin_ = new LockInSimulation;
        //lockin_ = new LockInSr830(gpib_);
        //ppms_ = new PpmsInstrument(gpib_, PPMSADDRESS);
    }
    else
    {
        //lockin_ = new LockInSimulation;
        lockin_ = new LockInSr830(gpib_);
        //ppms_ = new PpmsSimulation;

        ppms_ = new PpmsInstrument(gpib_, PPMSADDRESS);
    }

    connect(ppms_, &PpmsAbstract::newTempSP,
            this, &InstrumentManager::newTempSP);
    connect(ppms_, &PpmsAbstract::newMagSP,
            this, &InstrumentManager::newMagSP);
    connect(ppms_, &PpmsAbstract::newAngleSP,
            this, &InstrumentManager::newAngleSP);
    connect(lockin_, &LockInAbstract::newFreqSP,
            this, &InstrumentManager::newFreqSP);
    connect(lockin_, &LockInAbstract::newSensivitySP,
            this, &InstrumentManager::newSensivitySP);
    connect(lockin_, &LockInAbstract::newHarmonicSP,
            this, &InstrumentManager::newHarmonicSP);
    connect(ppms_, &PpmsAbstract::newErrorPPMS,
            this, &InstrumentManager::newErrorMessage);
    connect(lockin_, &LockInAbstract::newErrorLockIN,
            this, &InstrumentManager::newErrorMessage);
}

void InstrumentManager::openDevice()
{
    ppms_->openDevice();
    lockin_->openDevice();
}

void InstrumentManager::setTempSetpoint(double setpoint, double rate)
{
    ppms_->setTempSetpoint(setpoint, rate);
}

void InstrumentManager::setInputVoltage(double InputVoltage)
{
    lockin_->setInputVoltage(InputVoltage);
}

void InstrumentManager::setMagFieldSP(double magField, double magRate)
{
    ppms_->setMagField(magField,magRate);

}

void InstrumentManager::setAngle(double angle)
{
    ppms_->setAngle(angle);
}

void InstrumentManager::setFrequency(double freq)
{
    lockin_->setFreq(freq);
}

void InstrumentManager::setHarmonic(double harmonic)
{
    lockin_->setHarmonic(harmonic);
}

void InstrumentManager::rotatorState(bool rotator)
{
    ppms_->newRotatorstate(rotator);
}



void InstrumentManager::onPolling()
{
    DataPoint dataPoint;
    dataPoint.setPpmsdata(std::make_shared<const PpmsDataPoint>(ppms_->ppmsLogik()));
    dataPoint.setLockindata(std::make_shared<const LockInDataPoint>(lockin_->lockInLogik()));
    auto dPoint = std::make_shared<DataPoint>(dataPoint);
    emit newData(dPoint);
    lockin_->setSensivity(lockinsens_->setSensitivity(dPoint));
}
