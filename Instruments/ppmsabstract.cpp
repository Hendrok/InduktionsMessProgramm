#include "ppmsabstract.h"

void PpmsAbstract::setTempSetpoint(double setpoint, double rate)
{
    setTempSetpointCore(setpoint, rate);
}

void PpmsAbstract::setMagField(double magField, double magRate)
{
    setMagFieldCore(magField, magRate);
}

void PpmsAbstract::setAngle(double angle)
{
    setAngleCore(angle);
}
