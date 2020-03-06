#ifndef LOCKINSR830_H
#define LOCKINSR830_H

#include "Instruments_global.h"
#include <QObject>
#include <memory>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "lockindatapoint.h"
#include "lockinabstract.h"

class INSTRUMENTS_EXPORT LockInSr830 : public LockInAbstract
{
    Q_OBJECT
public:
    LockInSr830();    
protected:
    void setInputVoltageCore(double inputVoltage) override;
    void setFreqCore(double freq) override;
    void setHarmonicCore(int harmonicW) override;
    void setSensivityCore(int sensivity) override;
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
    double sensivity_;
    double harmonicW_;
    double phase_;
};

#endif
