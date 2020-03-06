#ifndef PPMSABSTRACT_H
#define PPMSABSTRACT_H
#include "Instruments_global.h"

#include <QObject>

class INSTRUMENTS_EXPORT PpmsAbstract : public QObject
{
    Q_OBJECT
public:
    void setTempSetpoint(double setpoint, double rate);
    void setMagField(double magField, double magRate);
    void setAngle(double angle);
protected:
    virtual void setTempSetpointCore(double setpoint,double rate) = 0;
    virtual void setMagFieldCore(double magField, double magRate) = 0;
    virtual void setAngleCore(double angle) = 0;
};

#endif // PPMSABSTRACT_H
