#include "ppmsinstrument.h"
#include <memory>
#include <QDebug>
#include <string>
#include <QPair>
#include <sstream>
#include <iomanip>
#include <algorithm>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "../InduControlCore/instrumentmanager.h"
#include "../Instruments/ppmsdatapoint.h"
#include "../Instruments/lockindatapoint.h"

const double MAXFIELDPPMS9 = 90000; //in Oe
const double MAXFIELDRATEPPMS9 = 190; //in Oe
const double MAXFIELDRATEPPMS14 = 120; //in Oe
const int DELAYGPIB = 100; //in ms
const bool TERMCHAR = false;
const int OE_IN_MT = 10;
const int BIT_STATUS = 1 << 0; // Stat
const int BIT_TEMP = 1 << 1; // Temp
const int BIT_MAG = 1 << 2; // Mag
const int BIT_ANGLE = 1 << 3; // Angle
const int BIT_PRESSURE = 1 << 19; // pressure
const int BIT_USERTEMP = 1 << 23; // userTemp

PpmsInstrument::PpmsInstrument(std::shared_ptr<GPIB> gpib, int address)
    : gpib_(gpib)
    , address_(address)
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
    gpib_->openDevice(address_);

    std::string idn = gpib_->query(address_, "*IDN?", DELAYGPIB, TERMCHAR);
    if(idn.find("QUANTUM DESIGN") == std::string::npos)
    {
        gpib_->closeDevice(address_);
    }

    if(!gpib_->isOpen(address_))
    {
        QString errormessage = "Ppms: ";
        if(gpib_->getError().size() == 0)
        {
            errormessage.append("Not connected");
        }
        else
        {
            errormessage.append(gpib_->getError().c_str());
        }
        emit newErrorPPMS(errormessage);
        return;
    }

    dataMask_ += BIT_STATUS; // Stat
    dataMask_ += BIT_TEMP; // Temp
    dataMask_ += BIT_MAG; // Mag
    dataMask_ += BIT_PRESSURE; // pressure

    QString magcnf;

    magcnf = (QString::fromStdString(gpib_->query(address_,"MAGCNF?", DELAYGPIB, TERMCHAR)));
    auto list = magcnf.split(',',QString::SkipEmptyParts);

    if (!list.isEmpty())
    {
        maxPosMagField_ = list[0].toDouble();
        maxRateMag_ = (maxPosMagField_ > MAXFIELDPPMS9) ? MAXFIELDRATEPPMS14 : MAXFIELDRATEPPMS9;
    }
}

bool PpmsInstrument::isOpen() const
{
    return gpib_->isOpen(address_);
}

void PpmsInstrument::setTempSetpointCore(double setpoint, double rate)
{
    if(!gpib_->isOpen(address_))
    {
        return;
    }

    std::string setTempSetpointStr = "TEMP "+ dtoStr(setpoint, 3) + " " + dtoStr(rate, 3) + " 0";
    gpib_->cmd(address_, setTempSetpointStr, DELAYGPIB, TERMCHAR);
}

void PpmsInstrument::setMagFieldCore(double magField, double magRate)
{
    if(!gpib_->isOpen(address_))
    {
        return;
    }

    std::string setMagFieldStr = "FIELD " + dtoStr(magField, 0) + " " + dtoStr(magRate, 0);
    gpib_->cmd(address_, setMagFieldStr, DELAYGPIB, TERMCHAR);
}

void PpmsInstrument::setAngleCore(double angle)
{
    if(!gpib_->isOpen(address_) || rotState_ == false)
    {
        return;
    }

    std::string angleStr = "MOVE " + std::to_string(angle);
    gpib_->cmd(address_, angleStr, DELAYGPIB, TERMCHAR);
}

void PpmsInstrument::setRotatorStateCore(bool rotator)
{
    rotState_ = rotator;

    if(rotator == true)
    {
        gpib_->cmd(address_ ,"Bridge 1,999.023,100.000,0,0,9.0", DELAYGPIB, TERMCHAR);
        gpib_->cmd(address_ ,"USERTEMP 23 1.9 1.8 2 1", DELAYGPIB, TERMCHAR);
        dataMask_ += BIT_ANGLE; // Angle
        dataMask_ += BIT_USERTEMP; // userTemp

        qDebug()<<gpib_->query(address_,"",DELAYGPIB,TERMCHAR).c_str();

        qDebug()<<dataMask_;
        rotState_ = ppmsLogik().datamask() & BIT_USERTEMP;
        if(rotState_ != rotator)
        {
            emit newErrorPPMS("Rotator not mounted");
        }
    }
    else
    {
        //TODO: Rotator Voltage aus?
        //gpib_->cmd(address_ ,"Bridge 0,999.023,100.000,0,0,9.0", DELAYGPIB, TERMCHAR);
        gpib_->cmd(address_ ,"USERTEMP 0", DELAYGPIB, TERMCHAR);
        dataMask_ -= BIT_ANGLE; // Angle
        dataMask_ -= BIT_USERTEMP; // userTemp
        //qDebug()<<dataMask_;
    }
}

QPair<double, double> PpmsInstrument::tempSetpointCore()
{
    if(!gpib_->isOpen(address_))
    {
        return QPair(0,0);
    }

    QString string = gpib_->query(address_, "TEMP?", DELAYGPIB, TERMCHAR).c_str();
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

    QString string = gpib_->query(address_, "FIELD?", DELAYGPIB, TERMCHAR).c_str();
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
    QString string = gpib_->query(address_, "MOVE?", DELAYGPIB, TERMCHAR).c_str();
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

    QString string = gpib_->query(address_, "LEVEL?", DELAYGPIB, TERMCHAR).c_str();
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
    QString getdat = (gpib_->query(address_, getDatStr , DELAYGPIB, TERMCHAR).c_str());

    auto Datavector = getdat.split(',');
    if(Datavector.size() < 5)
    {
        return ppmsDpoint;
    }
    ppmsDpoint.setDatamask(Datavector[0].toInt());
    ppmsDpoint.setPvStatusPpms(Datavector[2].toStdString());
    ppmsDpoint.setPvTempLive(Datavector[3].toDouble());
    ppmsDpoint.setPvMagFieldLive( Datavector[4].toDouble() / OE_IN_MT);
    ppmsDpoint.setPvSamplePressure(Datavector[5].toDouble());

    if(ppmsDpoint.datamask() & BIT_USERTEMP && rotState_ == true && Datavector.size()>7)
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









