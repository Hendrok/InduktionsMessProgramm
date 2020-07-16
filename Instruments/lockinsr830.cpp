#include "lockinsr830.h"
#include <memory>
#include <QDebug>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "../InduControlCore/instrumentmanager.h"
#include "../Instruments/ppmsdatapoint.h"
#include "../Instruments/lockindatapoint.h"

const int DELAYGPIB = 0;
const bool TERMCHAR = true;

LockInSr830::LockInSr830(std::shared_ptr<GPIB> gpib, int address)
    : datapoint_(DataPoint())
    , inputVoltage_ (0.1)
    , voltnow_(0.1)
    , freq_(0)
    , sensivity_(0)
    , harmonicW_(1)
    , phase_(0)
    , gpib_(gpib)
    , address_(address)
{  
    sstring_.imbue(std::locale::classic());
    sstring_ << std::fixed;
}

void LockInSr830::openDevice()
{
    if (gpib_ == nullptr)
    {
        return;
    }
    qDebug()<<"openDevice LOCKIN";
    gpib_->openDevice(address_);

    std::string idn = gpib_->query(address_, "*IDN?", DELAYGPIB, true);
    if(idn.find("SR830") == std::string::npos)
    {
        gpib_->closeDevice(address_);
    }

    if(!gpib_->isOpen(address_))
    {
        QString errormessage = "Lockin: ";
        if(gpib_->getError().size() == 0)
        {
            errormessage.append("Not connected");
        }
        else
        {
            errormessage.append(gpib_->getError().c_str());
        }
        emit newErrorLockIN(errormessage);
        return;
    }
}

void LockInSr830::setInputVoltageCore(double inputVoltage)
{
    if(!gpib_->isOpen(address_))
    {
        return;
    }
    auto inputVoltageStr = "SLVL " + dtoStr(inputVoltage, 3);
    gpib_->cmd(address_, inputVoltageStr, DELAYGPIB , true);
}

void LockInSr830::setFreqCore(double freq)
{
    if(!gpib_->isOpen(address_))
    {
        return;
    }
    auto freqStr = "FREQ " + dtoStr(freq, 3);
    gpib_->cmd(address_, freqStr, DELAYGPIB , true);
    std::string freqq = "FREQ?";
}

void LockInSr830::setHarmonicCore(int harmonicW)
{
    if(!gpib_->isOpen(address_))
    {
        return;
    }
    auto harmonicStr = "HARM " + itoStr(harmonicW);
    gpib_->cmd(address_, harmonicStr, DELAYGPIB , true);
}

void LockInSr830::setSensivityCore(int sensivity)
{
    if(!gpib_->isOpen(address_))
    {
        return;
    }
    auto sensivityStr = "SENS " + itoStr(sensivity);
    gpib_->cmd(address_, sensivityStr, DELAYGPIB , true);

}

double LockInSr830::inputVoltageCore()
{
    if(!gpib_->isOpen(address_))
    {
        return 0;
    }
    return strtoD(gpib_->query(address_,"SLVL?", DELAYGPIB , true));
}

double LockInSr830::freqCore()
{
    if(!gpib_->isOpen(address_))
    {
        return 0;
    }
    return strtoD(gpib_->query(address_, "FREQ?", DELAYGPIB , true));
}

int LockInSr830::harmonicCore()
{
    if(!gpib_->isOpen(address_))
    {
        return 0;
    }
    //TODO: harmonicabfrage
    return strtoI("1");
}

int LockInSr830::sensitivityCore()
{
    if(!gpib_->isOpen(address_))
    {
        return 0;
    }
    //TODO: sensivityabfrage
    return strtoI("1");
}

LockInDataPoint LockInSr830::lockInLogik()
{
    if(!gpib_->isOpen(address_))
    {
        return LockInDataPoint();
    }
    LockInDataPoint lockingDpoint;

    auto dataPoint =std::make_shared<DataPoint> ();
    lockingDpoint.setPvVoltInputLive(inputVoltageCore());

    lockingDpoint.setPvPhase(strtoD(gpib_->query(address_, "OUTP? 4", DELAYGPIB , true)));
    lockingDpoint.setPvVoltOutputLive(strtoD(gpib_->query(address_, "OUTP? 3", DELAYGPIB , true)));

    return lockingDpoint;
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
