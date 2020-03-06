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
     , magFieldSP_(0)
     , magRate_(0)
     , magFieldNow_(0)
     , angle_(0)
{
}
/*
void PpmsSimulation::setTempSetpoint(double setpoint, double rate)
{
    tempSetpoint_ = setpoint;
    tempRate_ = rate;
}

void PpmsSimulation::setMagField(double magField, double magRate)
{
    magFieldSP_ = magField;
    magRate_ = magRate;
}

void PpmsSimulation::setAngle(double angle)
{
    angle_ = angle;
}*/

void PpmsSimulation::setTempSetpointCore(double setpoint, double rate)
{
    tempSetpoint_ = setpoint;
    tempRate_ = rate;
    emit newTempSP(tempSetpoint_, tempRate_);
}

void PpmsSimulation::setMagFieldCore(double magField, double magRate)
{
    magFieldSP_ = magField;
    magRate_ = magRate;
    emit newMagSP(magFieldSP_, magRate_);
}

void PpmsSimulation::setAngleCore(double angle)
{
    angle_ = angle;
    emit newAngleSP(angle_);
}


PpmsDataPoint PpmsSimulation::generateVariables()
{
    PpmsDataPoint ppmsDpoint;


    auto dataPoint =std::make_shared<DataPoint> ();
    double test =QRandomGenerator::global()->bounded(1.0);

    ppmsDpoint.setPvVoltLive(test);  
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
        tempNow_ = tempNow_ - tempRate_;
    }
    if(std::abs(magFieldSP_ - magFieldNow_) < magRate_ && magRate_ > 0.1)
    {
        magRate_ = 0.1*magRate_;
    }

    if (magFieldNow_ < magFieldSP_)
    {
        magFieldNow_ = magFieldNow_ + magRate_;
    }
    if (magFieldNow_ > magFieldSP_)
    {
        magFieldNow_ = magFieldNow_ - magRate_;
    }
    ppmsDpoint.setPvTempLive(tempNow_);
    ppmsDpoint.setPvMagFieldLive(magFieldNow_);
    return ppmsDpoint;

}
