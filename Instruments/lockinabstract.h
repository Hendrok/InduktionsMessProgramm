#ifndef LOCKINABSTRACT_H
#define LOCKINABSTRACT_H
#include "Instruments_global.h"
#include <QObject>
#include "lockindatapoint.h"
class INSTRUMENTS_EXPORT LockInAbstract: public QObject
{
    Q_OBJECT
public:
    void setInputVoltage(double InputVoltage);
    void setFreq(double freq);
    void setSensivity(int sensivity);
    void setHarmonic(int harmonicW);
    virtual LockInDataPoint lockInLogik() = 0;
signals:
    virtual void newFreqSP(double freq) = 0;
    virtual void newSensivitySP(int sensivity) = 0;
    virtual void newHarmonicSP(int harmonicW) = 0;
protected:
    virtual void setInputVoltageCore(double InputVoltage) = 0;
    virtual void setFreqCore(double freq) = 0;
    virtual void setSensivityCore(int sensivity) = 0;
    virtual void setHarmonicCore(int harmonicW) = 0;
};

#endif // LOCKINABSTRACT_H
