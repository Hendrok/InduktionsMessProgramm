#ifndef PPMSSIMULATION_H
#define PPMSSIMULATION_H
#include "InduControlCore_global.h"
#include <QObject>
#include <memory>
#include "../InduCore/datapoint.h"

class QObject;
class MeasurementSequence;

class INDUCONTROLCORE_EXPORT PpmsSimulation: public QObject
{
    Q_OBJECT
public:
    PpmsSimulation();
    void setTempSetpoint(double setpoint, double rate);

    void getStartwerte(std::shared_ptr <MeasurementSequence> &measurementSequence);
public slots:
    std::shared_ptr <DataPoint> generateVariables();
private:
    DataPoint datapoint_;
    double tempSetpoint_;
    double tempRate_;
    double fieldSetpoint_;
    double fieldRate_;
};

#endif // PPMSSIMULATION_H
