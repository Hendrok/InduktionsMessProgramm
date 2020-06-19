#include "ppmsabstract.h"

void PpmsAbstract::setTempSetpoint(double setpoint, double rate)
{
    setTempSetpointCore(setpoint, rate);
    auto setpointReport = tempSetpointCore();
    emit newTempSP(setpointReport.first, setpointReport.second);
}

void PpmsAbstract::setMagField(double magField, double magRate)
{
    setMagFieldCore(magField, magRate);
    auto setpointReport = magFieldCore();
    emit newMagSP(setpointReport.first, setpointReport.second);
}

void PpmsAbstract::setAngle(double angle)
{
    setAngleCore(angle);
    auto angleReport = angleCore();
    emit newAngleSP(angleReport);
}

