#include "lockinsr830.h"
#include <memory>
#include <QDebug>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "../InduControlCore/instrumentmanager.h"
#include "../Instruments/ppmsdatapoint.h"
#include "../Instruments/lockindatapoint.h"

LockInSr830::LockInSr830()
    : datapoint_(DataPoint())
    , inputVoltage_ (0.1)
    , voltnow_(0.1)
    , freq_(0)
    , sensivity_(0)
    , harmonicW_(1)
    , phase_(0)
{  
    sstring_.imbue(std::locale::classic());
    sstring_ << std::fixed;
}

void LockInSr830::setInputVoltageCore(double inputVoltage)
{
    auto inputVoltageStr = "SLVL " + dtoStr(inputVoltage, 3);
}

void LockInSr830::setFreqCore(double freq)
{
    auto freqStr = "FREQ " + dtoStr(freq, 3);
}

void LockInSr830::setHarmonicCore(int harmonicW)
{
    auto harmonicStr = "HARM " + itoStr(harmonicW);
}

void LockInSr830::setSensivityCore(int sensivity)
{
    auto sensivityStr = "SENS " + itoStr(sensivity);
}

double LockInSr830::inputVoltageCore()
{
    return strtoD(0);
}

double LockInSr830::freqCore()
{
    return strtoD(0);
}

int LockInSr830::harmonicCore()
{
    return strtoI(0);
}

int LockInSr830::sensitivityCore()
{
    return strtoI(0);
}

LockInDataPoint LockInSr830::lockInLogik()
{

    LockInDataPoint lockingDpoint;

    auto dataPoint =std::make_shared<DataPoint> ();
    lockingDpoint.setPvPhase(phase_);
    lockingDpoint.setPvVoltInputLive(inputVoltage_);

    return lockingDpoint;
}

std::string LockInSr830::dtoStr(double number, int dec)
{    
    sstring_ << std::setprecision(dec) << number;
    return sstring_.str();
}

std::string LockInSr830::itoStr(int number)
{
    return std::to_string(number);
}

double LockInSr830::strtoD(std::string number)
{
    return std::stod(number);
}

int LockInSr830::strtoI(std::string number)
{
    return std::stod(number);
}
