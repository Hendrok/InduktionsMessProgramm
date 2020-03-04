#ifndef PPMSCORE_H
#define PPMSCORE_H
#include "Instruments_global.h"
#include <QObject>
#include <memory>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "ppmsdatapoint.h"


class INSTRUMENTS_EXPORT PpmsCore : public QObject
{
    Q_OBJECT
public:
    PpmsCore();
    void setTempSetpoint(double setpoint, double rate);
    void setMagField(double magField);
    void setAngle(double angle);
signals:
    void newTempSP(double setpoint, double rate);
    void newMagSP(double magField);
    void newAngleSP(double angle);
public slots:
    PpmsDataPoint receiveVariables();
private:
    DataPoint datapoint_;
    double tempSetpoint_;
    double tempRate_;
    double fieldSetpoint_;
    double fieldRate_;
    double ppmsHelium_;
    double tempNow_;
    double magField_;
    double angle_;
};

#endif // PPMSCORE_H
