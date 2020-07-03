#include "ppmsabstract.h"

const double MAXTEMP = 350;
const double MINTEMP = 1.9;
const double MAXRATE = 20;
const double MINRATE = 0.1;

const double MAXANGLE = 360;
const double MINANGLE = 0;

void PpmsAbstract::setTempSetpoint(double setpoint, double rate)
{
    if(setpoint > MAXTEMP)
    {
        setpoint = MAXTEMP;
    }
    if(setpoint < MINTEMP)
    {
        setpoint = MINTEMP;
    }
    if(rate > MAXRATE)
    {
        rate = MAXRATE;
    }
    if(rate < MINRATE)
    {
        rate = MINRATE;
    }

    setTempSetpointCore(setpoint, rate);
    auto setpointReport = tempSetpointCore();
    emit newTempSP(setpointReport.first, setpointReport.second);
}

void PpmsAbstract::setMagField(double magField, double magRate)
{
    Q_UNUSED(magRate);

    magField *= 10;

    if (maxPosMagField_ < magField)
    {
        magField = maxPosMagField_;
        QString errorMag = ("The maximum magField is too high and will automaticly be reduced to: ");
        errorMag.append(QString::number(maxPosMagField_));
        emit newErrorPPMS(errorMag);
    }
    if(ppmsHelium_ < 60)
    {
        magField = 0;
        QString errorhel =("Helium is too low for Magnetic Field!");
        emit newErrorPPMS(errorhel);
    }

    setMagFieldCore(magField, maxRateMag_);
    auto setpointReport = magFieldCore();
    emit newMagSP(setpointReport.first, setpointReport.second);
}

void PpmsAbstract::setAngle(double angle)
{
    if(angle > MAXANGLE)
    {
        angle = MAXANGLE;
    }
    if(angle < MINANGLE)
    {
        angle = MINANGLE;
    }

    setAngleCore(angle);
    auto angleReport = angleCore();
    emit newAngleSP(angleReport);
}


