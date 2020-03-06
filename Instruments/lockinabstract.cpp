#include "lockinabstract.h"

void LockInAbstract::setInputVoltage(double InputVoltage)
{
    setInputVoltageCore(InputVoltage);
}

void LockInAbstract::setFreq(double freq)
{
    setFreqCore(freq);
}

void LockInAbstract::setSensivity(int sensivity)
{
    setSensivityCore(sensivity);
}

void LockInAbstract::setHarmonic(int harmonicW)
{
    setHarmonicCore(harmonicW);
}
