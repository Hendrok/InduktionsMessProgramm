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

void LockInSr830::setInputVoltageCore(double inputVoltage)
{
    Q_UNUSED(inputVoltage);
}

void LockInSr830::setFreqCore(double freq)
{
    Q_UNUSED(freq);
}

void LockInSr830::setHarmonicCore(int harmonicW)
{
    Q_UNUSED(harmonicW);
}

void LockInSr830::setSensivityCore(int sensivity)
{
    Q_UNUSED(sensivity);
}

double LockInSr830::inputVoltageCore()
{
    return 0;
}

double LockInSr830::freqCore()
{
    return 0;
}

int LockInSr830::harmonicCore()
{
    return 0;
}

int LockInSr830::sensitivityCore()
{
    return 0;
}

LockInDataPoint LockInSr830::lockInLogik()
{

    LockInDataPoint lockingDpoint;

    auto dataPoint =std::make_shared<DataPoint> ();
    lockingDpoint.setPvPhase(phase_);
    lockingDpoint.setPvVoltLive(inputVoltage_);

    return lockingDpoint;
}
