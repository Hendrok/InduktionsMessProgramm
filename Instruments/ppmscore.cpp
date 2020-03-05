#include "ppmscore.h"
#include <memory>
#include <QDebug>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "../InduControlCore/instrumentmanager.h"
#include "../Instruments/ppmsdatapoint.h"
#include "../Instruments/lockindatapoint.h"

PpmsCore::PpmsCore()
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

void PpmsCore::setTempSetpoint(double setpoint, double rate)
{
    tempSetpoint_ = setpoint;
    tempRate_ = rate;
}

void PpmsCore::setMagField(double magField)
{
    magField_ = magField;
}

void PpmsCore::setAngle(double angle)
{
    angle_ = angle;
}

PpmsDataPoint PpmsCore::receiveVariables()
{
    PpmsDataPoint ppmsDpoint;
    auto dataPoint =std::make_shared<DataPoint> ();
    ppmsDpoint.setPvTempSetPoint(tempSetpoint_);
    ppmsDpoint.setPvTempRate(tempRate_);
    ppmsDpoint.setPvVoltLive(angle_);
    ppmsDpoint.setPvMagFieldLive(magField_);
    emit newTempSP(tempSetpoint_, tempRate_);
    emit newMagSP(magField_);
    emit newAngleSP(angle_);
    ppmsDpoint.setPvRotLive(angle_);

    return ppmsDpoint;
}







