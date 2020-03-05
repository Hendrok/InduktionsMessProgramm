#ifndef LOCKINSIMULATION_H
#define LOCKINSIMULATION_H

#include "Instruments_global.h"
#include <QObject>
#include <memory>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "lockindatapoint.h"

class INSTRUMENTS_EXPORT LockInSimulation : public QObject
{
    Q_OBJECT
public:
    LockInSimulation();
    void setInputVoltage(double InputVoltage);
    void setFreq(double freq);
    void setSensivity(int sensivity);
    void setHarmonic(int harmonicW);
signals:
    void newFreqSP(double freq);
    void newSensivitySP(int sensivity);
    void newHarmonicSP(int harmonicW);
public slots:
    LockInDataPoint lockInLogik();
private:
    DataPoint datapoint_;
    double inputVoltage_;
    double voltnow_;
    double freq_;
    int sensivity_;
    double harmonicW_;
};

#endif // LOCKINSIMULATION_H
