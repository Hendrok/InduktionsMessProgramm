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

    std::shared_ptr <DataPoint> generateVariables();
    void getStartwerte(std::shared_ptr <MeasurementSequence> &measurementSequence);
private:
    double starttemp_;
    double currenttemp_;
    double endtemp_;

};

#endif // PPMSSIMULATION_H
