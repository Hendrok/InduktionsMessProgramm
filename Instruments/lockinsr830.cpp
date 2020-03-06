#include "lockinsr830.h"
#include <memory>
#include <QDebug>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "../InduControlCore/instrumentmanager.h"
#include "../Instruments/ppmsdatapoint.h"
#include "../Instruments/lockindatapoint.h"

LockInSr830::LockInSr830()
    : datapoint_(DataPoint())
    , inputVoltage_ (0.1)
    , voltnow_(0.1)
    , freq_(0)
    , sensivity_(0)
    , harmonicW_(1)
    , phase_(0)
{  
}

void LockInSr830::setInputVoltage(double InputVoltage)
{
    inputVoltage_ = InputVoltage;
}

void LockInSr830::setFreq(double freq)
{
    freq_ = freq;
}

void LockInSr830::setSensivity(int sensivity)
{
    sensivity_ = sensivity;
}

void LockInSr830::setHarmonic(int harmonicW)
{
    harmonicW_ = harmonicW;
}

LockInDataPoint LockInSr830::lockInLogik()
{

    LockInDataPoint lockingDpoint;

    auto dataPoint =std::make_shared<DataPoint> ();
    lockingDpoint.setPvPhase(phase_);
    lockingDpoint.setPvVoltLive(inputVoltage_);

    return lockingDpoint;
}
