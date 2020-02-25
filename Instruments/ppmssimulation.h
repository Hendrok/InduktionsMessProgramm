#ifndef PPMSSIMULATION_H
#define PPMSSIMULATION_H
#include "Instruments_global.h"
#include <QObject>
#include <memory>

//Internal Classes
#include "../InduCore/datapoint.h"


class QObject;
class MeasSeqTc;


class INSTRUMENTS_EXPORT PpmsSimulation: public QObject
{
    Q_OBJECT
public:
    PpmsSimulation();
    void setTempSetpoint(double setpoint, double rate);

public slots:
    std::shared_ptr <DataPoint> generateVariablesTc();
private:
    DataPoint datapoint_;
    double tempSetpoint_;
    double tempRate_;
    double fieldSetpoint_;
    double fieldRate_;
    double ppmsHelium_;
    double tempNow_;

};

#endif // PPMSSIMULATION_H
