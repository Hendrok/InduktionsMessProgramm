#include "lockincore.h"
#include <memory>
#include <QDebug>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "../InduControlCore/instrumentmanager.h"
#include "../Instruments/ppmsdatapoint.h"
#include "../Instruments/lockindatapoint.h"

LockInCore::LockInCore()
    : datapoint_(DataPoint())
    , inputVoltage_ (0.1)
    , voltnow_(0.1)
    , freq_(0)
    , sensivity_(0)
    , harmonicW_(1)
    , phase_(0)
{  
}

void LockInCore::setInputVoltage(double InputVoltage)
{
    inputVoltage_ = InputVoltage;
}

void LockInCore::setFreq(double freq)
{
    freq_ = freq;
}

void LockInCore::setSensivity(double sensivity)
{
    sensivity_ = sensivity;
}

void LockInCore::setHarmonic(int harmonicW)
{
    harmonicW_ = harmonicW;
}

LockInDataPoint LockInCore::lockInLogik()
{

    LockInDataPoint lockingDpoint;

    auto dataPoint =std::make_shared<DataPoint> ();
    lockingDpoint.setPvPhase(phase_);
    lockingDpoint.setPvVoltLive(inputVoltage_);
    emit newFreqSP(freq_);
    emit newSensivitySP(sensivity_);
    emit newHarmonicSP(harmonicW_);


    return lockingDpoint;
}
