#include "instrumentmanager.h"
#include <QDebug>

//Internal Classes
#include "../Instruments/ppmssimulation.h"
#include "../Instruments/lockinsimulation.h"
#include "../Instruments/ppmsabstract.h"
#include "../Instruments/lockinabstract.h"
#include "../Instruments/ppmsinstrument.h"
#include "../Instruments/lockinsr830.h"
#include "../Instruments/gpib.h"


InstrumentManager::InstrumentManager()
    : timer_(new QTimer(this))
{
    connect(timer_, &QTimer::timeout,
            this, &InstrumentManager::onPolling);
    timer_->start(200);

    if(simulation_ == true)
    {
        ppms_ = new PpmsSimulation;
        auto gpib = std::make_shared<GPIB>();
        lockin_ = new LockInSr830(gpib); //BUG (nehme an hier passiert Fehler)
    }
    else
    {

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

void InstrumentManager::setSensivity(int sensivity)
{
    lockin_->setSensivity(sensivity);
}

void InstrumentManager::setHarmonic(double harmonic)
{
    lockin_->setHarmonic(harmonic);
}



void InstrumentManager::onPolling()
{
    DataPoint dataPoint;

    dataPoint.setPpmsdata(std::make_shared<const PpmsDataPoint>(ppms_->generateVariables()));
    dataPoint.setLockindata(std::make_shared<const LockInDataPoint>(lockin_->lockInLogik()));

    auto dPoint = std::make_shared<DataPoint>(dataPoint);
    emit newData(dPoint);
}
