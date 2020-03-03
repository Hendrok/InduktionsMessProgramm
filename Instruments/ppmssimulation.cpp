#include "ppmssimulation.h"
#include <QRandomGenerator>
#include <memory>
#include <QDebug>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "../InduControlCore/instrumentmanager.h"
#include "../Instruments/ppmsdatapoint.h"
#include "../Instruments/lockindatapoint.h"

PpmsSimulation::PpmsSimulation()
     : datapoint_(DataPoint())
     , tempSetpoint_(300)
     , tempRate_(10)
     , fieldSetpoint_(0)
     , fieldRate_(10)
     , ppmsHelium_(100)
     , tempNow_(300)
     , magField_(0)
     , angle_(0)

{
}

void PpmsSimulation::setTempSetpoint(double setpoint, double rate)
{
    tempSetpoint_ = setpoint;
    tempRate_ = rate;
}

void PpmsSimulation::setPpmsVariables(double magField, double angle)
{
    magField_ = magField;
    angle_ = angle;
}


PpmsDataPoint PpmsSimulation::generateVariables()
{
    PpmsDataPoint ppmsDpoint;


    auto dataPoint =std::make_shared<DataPoint> ();
    double test =QRandomGenerator::global()->bounded(1.0);

    ppmsDpoint.setPvTempSetPoint(tempSetpoint_);
    ppmsDpoint.setPvTempRate(tempRate_);
    ppmsDpoint.setPvVoltLive(test);
    ppmsDpoint.setPvMagSetPoint(magField_);
    ppmsDpoint.setPvMagFieldLive(magField_);
    ppmsDpoint.setPvRotSetPoint(angle_);
    ppmsDpoint.setPvRotLive(angle_);


    if(std::abs(tempSetpoint_ - tempNow_) < tempRate_ && tempRate_ > 0.1)
    {
        tempRate_ = 0.1*tempRate_;
    }

    if (tempNow_ < tempSetpoint_)
    {
        tempNow_ = tempNow_ + tempRate_;
    }
    if (tempNow_ > tempSetpoint_)
    {
        tempNow_ = tempNow_-tempRate_;
    }

    ppmsDpoint.setPvTempLive(tempNow_);

    return ppmsDpoint;

}
