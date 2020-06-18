#include "ppmsinstrument.h"
#include <memory>
#include <QDebug>
#include <string>
#include <QPair>
#include <sstream>
#include <iomanip>
//Internal Classes
#include "../InduCore/datapoint.h"
#include "../InduControlCore/instrumentmanager.h"
#include "../Instruments/ppmsdatapoint.h"
#include "../Instruments/lockindatapoint.h"

PpmsInstrument::PpmsInstrument(std::shared_ptr<GPIB> gpib)
    : datapoint_(DataPoint())
    , tempSetpoint_(300)
    , tempRate_(10)
    , fieldSetpoint_(0)
    , fieldRate_(10)
    , ppmsHelium_(100)
    , tempNow_(300)
    , magField_(0)
    , angle_(0)
    , gpib_(gpib)
    , address_(15)
{   
    openDevice();
    sstring_.imbue(std::locale::classic());
    sstring_ << std::fixed;

}

void PpmsInstrument::setTempSetpointCore(double setpoint, double rate)
{
    if(setpoint > 350)
    {
        setpoint = 350;
    }
    if(setpoint < 1.9)
    {
        setpoint = 1.9;
    }
    if(rate > 20)
    {
        rate = 20;
    }
    if(rate < 0)
    {
        rate = 0.1;
    }
    std::string setTempSetpointStr= dtoStr(setpoint, 3) + " " + dtoStr(rate, 3) + " 0";
    gpib_->cmd(address_, setTempSetpointStr);
}

void PpmsInstrument::setMagFieldCore(double magField, double magRate)
{
    //TODO: Abfrage MagField, spezifisch für 9/14 T!
    //transform to oe
    magField = magField *10;
    magRate = magRate *10;
    std::string setMagFieldStr= dtoStr(magField, 0) + " " + dtoStr(magRate, 0);
    gpib_->cmd(address_, setMagFieldStr);
}

void PpmsInstrument::setAngleCore(double angle)
{
    std::string angleStr = itoStr(angle);
    gpib_->cmd(address_, angleStr);
}


QPair<double, double> PpmsInstrument::tempSetpointCore()
{

    return QPair(strtoD(gpib_->query(address_,"TEMP?")),0);
}

QPair<double, double> PpmsInstrument::magFieldCore()
{
    return QPair(strtoD(gpib_->query(address_,"FIELD?")),0);
}

double PpmsInstrument::angleCore()
{
    return strtoD(gpib_->query(address_, "ANGLE?"));   //TODO: Befehl nachgucken ist geraten, Befehl wohl unnötig da im Pppms status schon vorhanden.
}

double PpmsInstrument::heliumCore()
{
    return strtoD(gpib_->query(address_, "LEVEL?"));
}

std::string PpmsInstrument::ppmsStatus()
{
    return gpib_->query(address_, "GETDAT? 524295 1");
}

PpmsDataPoint PpmsInstrument::ppmsLogik()
{
    PpmsDataPoint ppmsDpoint;
    auto dataPoint =std::make_shared<DataPoint> ();
    ppmsDpoint.setPvTempLive(tempSetpointCore().first);
    ppmsDpoint.setPvMagFieldLive(magFieldCore().first);
    ppmsDpoint.setPvChamberLevel(heliumCore());
    ppmsDpoint.setPvStatusPpms(ppmsStatus());
    return ppmsDpoint;
}

void PpmsInstrument::openDevice()
{
    if (gpib_ == nullptr) {
        return;
    }
    qDebug()<<"openDevice";
    gpib_->openDevice(15);
}
std::string PpmsInstrument::dtoStr(double number,int dec)
{
    sstring_.str(std::string());
    sstring_ << std::setprecision(dec) << number;
    return sstring_.str();
}

std::string PpmsInstrument::itoStr(int number)
{
    return std::to_string(number);

}

double PpmsInstrument::strtoD(std::string number)
{
    return std::stod(number);

}

int PpmsInstrument::strtoI(std::string number)
{
    return std::stod(number);

}








