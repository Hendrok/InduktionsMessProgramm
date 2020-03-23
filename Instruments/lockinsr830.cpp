#include "lockinsr830.h"
#include <memory>
#include <QDebug>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "../InduControlCore/instrumentmanager.h"
#include "../Instruments/ppmsdatapoint.h"
#include "../Instruments/lockindatapoint.h"

LockInSr830::LockInSr830(std::shared_ptr<GPIB> gpib)
    : datapoint_(DataPoint())
    , inputVoltage_ (0.1)
    , voltnow_(0.1)
    , freq_(0)
    , sensivity_(0)
    , harmonicW_(1)
    , phase_(0)
    , gpib_(gpib)
    , address_(10)
{  
    openDevice();
    sstring_.imbue(std::locale::classic());
    sstring_ << std::fixed;
}

void LockInSr830::setInputVoltageCore(double inputVoltage)
{
    auto inputVoltageStr = "SLVL " + dtoStr(inputVoltage, 3);
    gpib_->cmd(address_, inputVoltageStr);
}

void LockInSr830::setFreqCore(double freq)
{
    auto freqStr = "FREQ " + dtoStr(freq, 3);
    gpib_->cmd(address_, freqStr);
    std::string freqq = "FREQ?";
}

void LockInSr830::setHarmonicCore(int harmonicW)
{
    auto harmonicStr = "HARM " + itoStr(harmonicW);
    gpib_->cmd(address_, harmonicStr);
}

void LockInSr830::setSensivityCore(int sensivity)
{
    auto sensivityStr = "SENS " + itoStr(sensivity);
    gpib_->cmd(address_, sensivityStr);
}

double LockInSr830::inputVoltageCore()
{
    return strtoD(gpib_->query(address_,"SLVL?"));
}

double LockInSr830::freqCore()
{
    return strtoD("1");
}

int LockInSr830::harmonicCore()
{
    return strtoI("1");
}

int LockInSr830::sensitivityCore()
{
    return strtoI("1");
}

LockInDataPoint LockInSr830::lockInLogik()
{

    LockInDataPoint lockingDpoint;

    auto dataPoint =std::make_shared<DataPoint> ();
    lockingDpoint.setPvVoltInputLive(inputVoltageCore());
    lockingDpoint.setPvPhase(strtoD(gpib_->query(address_, "OUTP? 4")));
    lockingDpoint.setPvVoltOutputLive(strtoD(gpib_->query(address_, "OUTP? 3")));
    // TODO: 3/4 nochmal durchlesen! Werte sind zwar richtig, aber scheinen sehr zeitversetzt?
    return lockingDpoint;
}

void LockInSr830::openDevice()
{
    if (gpib_ == nullptr) {
        return;
    }
    qDebug()<<"openDevice";
    gpib_->openDevice(10);
}

std::string LockInSr830::dtoStr(double number, int dec)
{
    sstring_.str(std::string());
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
