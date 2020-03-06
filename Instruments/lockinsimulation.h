#ifndef LOCKINSIMULATION_H
#define LOCKINSIMULATION_H

#include "Instruments_global.h"
#include <QObject>
#include <memory>
#include <QPair>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "lockindatapoint.h"
#include "lockinabstract.h"

class INSTRUMENTS_EXPORT LockInSimulation : public LockInAbstract
{
    Q_OBJECT
public:
    LockInSimulation();

protected:
    void setInputVoltageCore(double inputVoltage) override;
    void setFreqCore(double freq) override;
    void setSensivityCore(int sensivity) override;
    void setHarmonicCore(int harmonicW) override;
    double inputVoltageCore() override;
    double freqCore() override;
    int harmonicCore() override;
    int sensitivityCore() override;
    LockInDataPoint lockInLogik() override;
private:
    DataPoint datapoint_;
    double inputVoltage_;
    double voltnow_;
    double freq_;
    int sensivity_;
    double harmonicW_;
};

#endif // LOCKINSIMULATION_H
