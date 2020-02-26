#ifndef LOCKINSIMULATION_H
#define LOCKINSIMULATION_H

#include "Instruments_global.h"
#include <QObject>
#include <memory>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "lockindatapoint.h"

class INSTRUMENTS_EXPORT LockInSimulation: public QObject
{
    Q_OBJECT

public:
    LockInSimulation();
    void setVoltSetPoint(double setpoint, double voltrate);
public slots:
    std::shared_ptr <DataPoint> lockInLogik();
private:
    DataPoint datapoint_;
    double voltSetpoint_;
    double voltRate_;
    double voltnow_;
};

#endif // LOCKINSIMULATION_H
