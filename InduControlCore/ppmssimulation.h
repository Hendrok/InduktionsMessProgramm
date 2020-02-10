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
    std::shared_ptr <DataPoint> generateVariables();
    void getStartwerte(std::shared_ptr <MeasurementSequence> &measurementSequence);
private:
    DataPoint datapoint_;
    double tempSetpoint_;
    double tempRate_;
    double fieldSetpoint_;
    double fieldRate_;
    double starttemp_;
    double currenttemp_;
    double endtemp_;

};

#endif // PPMSSIMULATION_H
