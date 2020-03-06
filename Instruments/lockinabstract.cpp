#include "lockinabstract.h"

void LockInAbstract::setInputVoltage(double InputVoltage)
{
    setInputVoltageCore(InputVoltage);
}

void LockInAbstract::setFreq(double freq)
{
    setFreqCore(freq);
    auto freqReport = freqCore();
    emit newFreqSP(freqReport);
}

void LockInAbstract::setSensivity(int sensivity)
{
    setSensivityCore(sensivity);
    auto sensivityReport = sensitivityCore();
    emit newSensivitySP(sensivityReport);
}

void LockInAbstract::setHarmonic(int harmonicW)
{
    setHarmonicCore(harmonicW);
    emit harmonicCore();
}
