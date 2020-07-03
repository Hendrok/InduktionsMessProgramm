#include "ppmssimulation.h"
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
     , tempNow_(300)
     , magFieldSP_(0)
     , magRate_(0)
     , magFieldNow_(0)
     , angle_(0)
{
    maxPosMagField_ = 9000;
    maxRateMag_ = 100;
    ppmsHelium_ = 60;
}
void PpmsSimulation::setTempSetpointCore(double setpoint, double rate)
{
    tempSetpoint_ = setpoint;
    tempRate_ = rate;

}

void PpmsSimulation::setMagFieldCore(double magField, double magRate)
{
    magFieldSP_ = magField;
    magRate_ = magRate;

}

void PpmsSimulation::setAngleCore(double angle)
{
    angle_ = angle;
}

QPair<double, double> PpmsSimulation::tempSetpointCore()
{
    return QPair(tempSetpoint_, tempRate_);
}

QPair<double, double> PpmsSimulation::magFieldCore()
{  
    if(magFieldSP_>9000)
    {
        emit newErrorPPMS("Magnetfeld zu hoch");
    }
    return QPair(magFieldSP_, magRate_);
}

double PpmsSimulation::angleCore()
{
    return angle_;
}

double PpmsSimulation::heliumCore()
{
    return ppmsHelium_;
}

PpmsDataPoint PpmsSimulation::ppmsLogik()
{
    PpmsDataPoint ppmsDpoint;
    auto dataPoint =std::make_shared<DataPoint> ();



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
    ppmsDpoint.setPvRotLive(angle_);
    ppmsDpoint.setPvSamplePressure(1);
    ppmsDpoint.setPvStatusPpms("4369");
    ppmsDpoint.setPvUserTemp(300);

    return ppmsDpoint;
}




