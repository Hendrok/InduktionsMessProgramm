#ifndef PPMSSIMULATION_H
#define PPMSSIMULATION_H
#include "InduControlCore_global.h"
#include <QObject>
#include <memory>
#include "../InduCore/datapoint.h"


class QObject;
class MeasSeqTc;


class INDUCONTROLCORE_EXPORT PpmsSimulation: public QObject
{
    Q_OBJECT
public:
    PpmsSimulation();
    void setTempSetpoint(double setpoint, double rate);

public slots:
    std::shared_ptr <DataPoint> generateVariables();
private:
    DataPoint datapoint_;
    double tempSetpoint_;
    double tempRate_;
    double measrunning_;
    double fieldSetpoint_;
    double fieldRate_;
    double ppmsHelium_;
    double tempNow_;

};

#endif // PPMSSIMULATION_H
