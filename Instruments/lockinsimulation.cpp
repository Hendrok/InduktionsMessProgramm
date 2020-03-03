#include "lockinsimulation.h"
#include <QRandomGenerator>
#include <memory>
#include <QDebug>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "../InduControlCore/instrumentmanager.h"
#include "../Instruments/ppmsdatapoint.h"
#include "../Instruments/lockindatapoint.h"

LockInSimulation::LockInSimulation()
    : datapoint_(DataPoint())
    , inputVoltage_ (0.1)
    , voltnow_(0.1)
    , freq_(0)
    , sensivity_(0)
    , harmonicW_(1)
{  
}

void LockInSimulation::SetInputVoltage(double InputVoltage)
{
    inputVoltage_ = InputVoltage;
}

void LockInSimulation::setLockVariables(double freq, double sensivity, int harmonicW)
{
    freq_ = freq;
    sensivity_ = sensivity;
    harmonicW_ = harmonicW;
}



LockInDataPoint LockInSimulation::lockInLogik()
{
    LockInDataPoint lockingDpoint;

    auto dataPoint =std::make_shared<DataPoint> ();
    double test =QRandomGenerator::global()->bounded(1.0)+90;

    lockingDpoint.setPvPhase(test);
    lockingDpoint.setPvVoltLive(inputVoltage_);
    lockingDpoint.setPvFreq(freq_);
    lockingDpoint.setPvSens(sensivity_);
    lockingDpoint.setPvHarmonicW(harmonicW_);


    return lockingDpoint;

}
