#ifndef PPMSABSTRACT_H
#define PPMSABSTRACT_H
#include "Instruments_global.h"
#include "QPair"
#include <QObject>
#include "ppmsdatapoint.h"


class INSTRUMENTS_EXPORT PpmsAbstract : public QObject
{
    Q_OBJECT
public:
    void setTempSetpoint(double setpoint, double rate);
    void setMagField(double magField, double magRate);
    void setAngle(double angle);
    virtual PpmsDataPoint generateVariables() =0;
protected:
    virtual void setTempSetpointCore(double setpoint,double rate) = 0;
    virtual void setMagFieldCore(double magField, double magRate) = 0;
    virtual void setAngleCore(double angle) = 0;
    virtual QPair<double,double> tempSetpointCore() = 0;
    virtual QPair<double, double> magFieldCore() = 0;
    virtual double angleCore() = 0;

signals:
    void newTempSP(double setpoint, double rate) ;
    void newMagSP(double magField, double magRate) ;
    void newAngleSP(double angle) ;

};

#endif // PPMSABSTRACT_H
