#ifndef PPMSSIMULATION_H
#define PPMSSIMULATION_H
#include "InduControlCore_global.h"
#include <QObject>
#include "../InduCore/datapoint.h"
#include "../InduCore/measurementsequence.h"
class QObject;

class INDUCONTROLCORE_EXPORT PpmsSimulation: public QObject
{
    Q_OBJECT
public:
    PpmsSimulation();
    void GenerateVariables();
private:
    double starttemp_;
    double endtemp_;
    double currenttemp_;
};

#endif // PPMSSIMULATION_H
