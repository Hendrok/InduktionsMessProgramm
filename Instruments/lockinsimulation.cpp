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
    , voltSetpoint_(0.1)
    , voltRate_(0.01)
    , voltnow_(0.1)
{  
}

void LockInSimulation::setVoltSetPoint(double setpoint, double voltrate)
{
    voltSetpoint_ = setpoint;
    voltRate_ = voltrate;
}

std::shared_ptr<DataPoint> LockInSimulation::lockInLogik()
{
    LockInDataPoint lockingDpoint;

    auto dataPoint =std::make_shared<DataPoint> ();
    double test =QRandomGenerator::global()->bounded(1.0)+90;

    lockingDpoint.setPvVoltSetPoint(voltSetpoint_);
    lockingDpoint.setPvVoltRate(voltRate_);
    lockingDpoint.setPvPhase(test);

    /*if(std::abs(voltSetpoint_ - voltnow_) < voltRate_)
    {
        voltRate_ = 0.1*voltRate_;
    }

    if (voltnow_ < voltSetpoint_)
    {
        voltnow_ = voltnow_ + voltRate_;
    }
    if (voltnow_ > voltSetpoint_)
    {
        voltnow_ = voltnow_-voltRate_;
    }
    */
    lockingDpoint.setPvVoltLive(voltnow_);

    dataPoint->setLockindata(std::make_shared<const LockInDataPoint> (lockingDpoint));
    return dataPoint;

}
