#ifndef PPMSABSTRACT_H
#define PPMSABSTRACT_H
#include "Instruments_global.h"
#include "QPair"
#include <QObject>
#include "ppmsdatapoint.h"
#include <vector>
#include <QTimer>

class INSTRUMENTS_EXPORT PpmsAbstract : public QObject
{
    Q_OBJECT
public:
    void setTempSetpoint(double setpoint, double rate);
    void setMagField(double magField, double magRate);
    void setAngle(double angle);
    virtual PpmsDataPoint ppmsLogik() = 0;
    virtual void openDevice() = 0;
    virtual void newRotatorstate(bool rot) = 0;
    virtual bool isOpen() const = 0;

protected:
    virtual void setTempSetpointCore(double setpoint,double rate) = 0;
    virtual void setMagFieldCore(double magField, double magRate) = 0;
    virtual void setAngleCore(double angle) = 0;
    virtual QPair<double,double> tempSetpointCore() = 0;
    virtual QPair<double, double> magFieldCore() = 0;
    virtual double angleCore() = 0;
    virtual double heliumCore() = 0;
    double maxPosMagField_ = 0;
    double maxRateMag_ = 0;
    double ppmsHelium_ = 0;
signals:
    void newTempSP(double setpoint, double rate) ;
    void newMagSP(double magField, double magRate) ;
    void newAngleSP(double angle) ;   
    void newErrorPPMS(QString ppmsError);
};

#endif // PPMSABSTRACT_H
