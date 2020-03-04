#ifndef PPMSSIMULATION_H
#define PPMSSIMULATION_H
#include "Instruments_global.h"
#include <QObject>
#include <memory>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "ppmsdatapoint.h"

class INSTRUMENTS_EXPORT PpmsSimulation : public QObject
{
    Q_OBJECT
public:
    PpmsSimulation();
    void setTempSetpoint(double setpoint, double rate);
    void setMagField(double magField, double magRate);
    void setAngle(double angle);
signals:
    void newTempSP(double setpoint, double rate);
    void newMagSP(double magField, double magRate);
    void newAngleSP(double angle);
public slots:
    PpmsDataPoint generateVariables();
private:
    DataPoint datapoint_;
    double tempSetpoint_;
    double tempRate_;
    double fieldSetpoint_;
    double fieldRate_;
    double ppmsHelium_;
    double tempNow_;
    double magFieldSP_;
    double magRate_;
    double magFieldNow_;
    double angle_;

};

#endif // PPMSSIMULATION_H
