#include "lockinsimulation.h"
#include <QRandomGenerator>
#include <memory>
#include <QDebug>
#include <QTime>
//Internal Classes
#include "../InduCore/datapoint.h"
#include "../InduControlCore/instrumentmanager.h"
#include "../Instruments/ppmsdatapoint.h"
#include "../Instruments/lockindatapoint.h"
#include <windows.h> // for Sleep

LockInSimulation::LockInSimulation()
    : datapoint_(DataPoint())
    , inputVoltage_ (0.1)
    , voltnow_(0.1)
    , freq_(0)
    , sensivity_(0)
    , harmonicW_(1)
{  
}

void LockInSimulation::openDevice()
{

}

void LockInSimulation::setInputVoltageCore(double inputVoltage)
{
    inputVoltage_ = inputVoltage;
}

void LockInSimulation::setFreqCore(double freq)
{
    freq_ = freq;
}

void LockInSimulation::setSensivityCore(int sensivity)
{
    sensivity_ = sensivity;
}

void LockInSimulation::setHarmonicCore(int harmonicW)
{
    harmonicW_ = harmonicW;
}

void LockInSimulation::delay()
{
  //  _sleep(1000);
}

double LockInSimulation::inputVoltageCore()
{
    return inputVoltage_;
}

double LockInSimulation::freqCore()
{
    return freq_;
}

int LockInSimulation::sensitivityCore()
{
    return sensivity_;
}

int LockInSimulation::harmonicCore()
{
    return harmonicW_;
}

LockInDataPoint LockInSimulation::lockInLogik()
{
    LockInDataPoint lockingDpoint;

    auto dataPoint =std::make_shared<DataPoint> ();
    double test =QRandomGenerator::global()->bounded(1.0);
    delay();
    lockingDpoint.setPvVoltOutputLive(test);
    lockingDpoint.setPvPhase(test+90);
    lockingDpoint.setPvVoltInputLive(inputVoltage_);

    return lockingDpoint;

}
