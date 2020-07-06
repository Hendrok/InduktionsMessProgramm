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

const double MAXFIELDPPMS9 = 90000; //in Oe
const double MAXFIELDRATEPPMS9 = 190; //in Oe
const double MAXFIELDRATEPPMS14 = 120; //in Oe
const int DELAYGPIB = 100; //in ms
const int OE_IN_MT = 10;
const int BITSTATUS = 1 << 0; // Stat
const int BITTEMP = 1 << 1; // Temp
const int BITMAG = 1 << 2; // Mag
const int BITANGLE = 1 << 3; // Angle
const int BITPRESSURE = 1 << 19; // pressure
const int BITUSERTEMP = 1 << 23; // userTemp

PpmsInstrument::PpmsInstrument(std::shared_ptr<GPIB> gpib, int address)
    : gpib_(gpib)
    , address_(address)
    , rotState_(false)
    , dataMask_(0)
{
    sstring_.imbue(std::locale::classic());
    sstring_ << std::fixed;
}

void PpmsInstrument::openDevice()
{
    if (gpib_ == nullptr) {
        return;
    }
    qDebug()<<"openDevice PPMS";
    gpib_->openDevice(address_, DELAYGPIB, false);
    if(!gpib_->isOpen(address_))
    {
        QString errormessage = "Ppms: ";
        errormessage.append(gpib_->getError().c_str());
        emit newErrorPPMS(errormessage);
        return;
    }

    dataMask_ += BITSTATUS; // Stat
    dataMask_ += BITTEMP; // Temp
    dataMask_ += BITMAG; // Mag
    dataMask_ += BITPRESSURE; // pressure

    if(rotState_ == true)
    {
        dataMask_ += BITANGLE; // Angle
        dataMask_ += BITUSERTEMP; // userTemp
    }

    QString magcnf;

    magcnf = (QString::fromStdString(gpib_->query(address_,"MAGCNF?", DELAYGPIB, false)));
    auto list = magcnf.split(',',QString::SkipEmptyParts);

    maxPosMagField_ = list[0].toDouble();
    maxRateMag_ = (maxPosMagField_ > MAXFIELDPPMS9) ? MAXFIELDRATEPPMS14 : MAXFIELDRATEPPMS9;
}

void PpmsInstrument::newRotatorstate(bool rotator)
{
    if(rotator == true)
    {
        gpib_->cmd(address_ ,"Bridge 1,999.023,100.000,0,0,9.0", DELAYGPIB, false);
        gpib_->cmd(address_ ,"USERTEMP 23 1.9 1.8 2 1", DELAYGPIB, false);
        rotState_ = true;
        dataMask_ += BITANGLE; // Angle
        dataMask_ += BITUSERTEMP; // userTemp
        qDebug()<<dataMask_;
    }
    else
    {
        //TODO: Rotator Voltage aus?
        //gpib_->cmd(address_ ,"Bridge 1,999.023,100.000,0,0,9.0", DELAYGPIB, false);
        gpib_->cmd(address_ ,"USERTEMP 0", DELAYGPIB, false);
        rotState_ = false;
        dataMask_ -= BITANGLE; // Angle
        dataMask_ -= BITUSERTEMP; // userTemp
        qDebug()<<dataMask_;
    }
}

void PpmsInstrument::setTempSetpointCore(double setpoint, double rate)
{
    if(!gpib_->isOpen(address_))
    {
        return;
    }
    std::string setTempSetpointStr = "TEMP "+ dtoStr(setpoint, 3) + " " + dtoStr(rate, 3) + " 0";
    gpib_->cmd(address_, setTempSetpointStr, DELAYGPIB, false);
}

void PpmsInstrument::setMagFieldCore(double magField, double magRate)
{
    if(!gpib_->isOpen(address_))
    {
        return;
    }
    std::string setMagFieldStr = "FIELD " + dtoStr(magField, 0) + " " + dtoStr(magRate, 0);
    gpib_->cmd(address_, setMagFieldStr, DELAYGPIB, false);
}

void PpmsInstrument::setAngleCore(double angle)
{
    if(!gpib_->isOpen(address_) || rotState_ == false)
    {
        return;
    }
    std::string angleStr = "MOVE " + std::to_string(angle);
    gpib_->cmd(address_, angleStr, DELAYGPIB, false);
}

QPair<double, double> PpmsInstrument::tempSetpointCore()
{
    if(!gpib_->isOpen(address_))
    {
        return QPair(0,0);
    }

    QString string = gpib_->query(address_, "TEMP?", DELAYGPIB, false).c_str();
    //QString besteht z.b aus (300,20.0)
    auto list = string.split(',', QString::SkipEmptyParts);
    //nur die erste Zahl die herausgegebn wird ist für uns wichtig
    return QPair(list[0].toDouble(),list[1].toDouble());
}

QPair<double, double> PpmsInstrument::magFieldCore()
{
    if(!gpib_->isOpen(address_))
    {
        return QPair(0,0);
    }
    QString string = gpib_->query(address_, "FIELD?", DELAYGPIB, false).c_str();
    //QString = String den uns Ppms gibt
    auto list = string.split(',', QString::SkipEmptyParts);
    //nur die erste Zahl die herausgegebn wird ist für uns wichtig
    return QPair(list[0].toDouble() / OE_IN_MT,list[1].toDouble() / OE_IN_MT); // inklusive Umrechnung in Oe
}

double PpmsInstrument::angleCore()
{
    if(!gpib_->isOpen(address_) || rotState_ == false)
    {
        return 0;
    }
    QString string = gpib_->query(address_, "MOVE?", DELAYGPIB, false).c_str();
    //QString = String den uns Ppms gibt
    auto list = string.split(',', QString::SkipEmptyParts);
    //nur die erste Zahl die herausgegebn wird ist für uns wichtig
    return list[0].toDouble();
}

double PpmsInstrument::heliumCore()
{
    if(!gpib_->isOpen(address_))
    {
        return 0;
    }
    QString string = gpib_->query(address_, "LEVEL?", DELAYGPIB, false).c_str();
    //QString = String den uns Ppms gibt
    auto list = string.split(',', QString::SkipEmptyParts);
    //nur die erste Zahl die herausgegebn wird ist für uns wichtig
    ppmsHelium_ = list[0].toDouble();
    return ppmsHelium_;
}

PpmsDataPoint PpmsInstrument::ppmsLogik()
{
    if(!gpib_->isOpen(address_))
    {
        return PpmsDataPoint();
    }
    PpmsDataPoint ppmsDpoint;
    std::string dataMask = QString::number(dataMask_).toStdString();
    std::string getDatStr = "GETDAT? " + dataMask + " 0";
    QString getdat = (gpib_->query(address_, getDatStr , DELAYGPIB, false).c_str());

    auto Datavector = getdat.split(',');
    if(Datavector.size() == 0)
    {
        return ppmsDpoint;
    }
    ppmsDpoint.setPvStatusPpms(Datavector[2].toStdString());
    ppmsDpoint.setPvTempLive(Datavector[3].toDouble());
    ppmsDpoint.setPvMagFieldLive( Datavector[4].toDouble() / OE_IN_MT);
    ppmsDpoint.setPvSamplePressure(Datavector[5].toDouble());

    if(Datavector[0].toInt() & BITUSERTEMP && rotState_ == true)
    {
        ppmsDpoint.setPvRotLive(Datavector[5].toDouble());
        ppmsDpoint.setPvSamplePressure(Datavector[6].toDouble());
        ppmsDpoint.setPvUserTemp(Datavector[7].toDouble());
    }

    ppmsDpoint.setPvChamberLevel(heliumCore());

    return ppmsDpoint;
}

std::string PpmsInstrument::dtoStr(double number,int dec)
{
    sstring_.str(std::string());
    sstring_ << std::setprecision(dec) << number;
    return sstring_.str();
}









