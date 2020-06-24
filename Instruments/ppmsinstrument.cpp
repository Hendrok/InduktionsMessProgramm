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
     std::string setTempSetpointStr= "TEMP "+ dtoStr(setpoint, 3) + " " + dtoStr(rate, 3) + " 0";
    gpib_->cmd(address_, setTempSetpointStr);
}

void PpmsInstrument::setMagFieldCore(double magField, double magRate)
{
    //Safety for 9t

    //Umrechnung in Oe
    magField = magField *10;
    magRate = magRate *10;

    QString magcnf;
    //QString = String den uns Ppms gibt
    magcnf=(QString::fromStdString(gpib_->query(address_,"MAGCNF?")));
    auto list = magcnf.split(',',QString::SkipEmptyParts);
    //nur die erste Zahl die herausgegebn wird ist für uns wichtig
    double maxPosMagField = list[0].toDouble();

    if(maxPosMagField>90000)
        magRate = 120;
    else
        magRate =190;


    if (maxPosMagField < magField)
    {
        magField=maxPosMagField;
        QString errorMag =( "The maximum magField is too high and will automaticly be reduced to: ");
        errorMag.append(QString::number(maxPosMagField));
        emit newErrorMagSp(errorMag);
    }
    //Safety to protect ppms:
    if(strtoD(gpib_->query(address_, "LEVEL?"))<60)
    {
        magField=0;
        QString errorhel =("Helium is too low for Magnetic Field!");
        emit newErrorMagHel(errorhel);
    }

    std::string setMagFieldStr= "Field " +dtoStr(magField, 0) + " " + dtoStr(magRate, 0);
    gpib_->cmd(address_, setMagFieldStr);
}

void PpmsInstrument::setAngleCore(double angle)
{
    std::string angleStr = "ANGLE" + itoStr(angle);
    gpib_->cmd(address_, angleStr);
}


QPair<double, double> PpmsInstrument::tempSetpointCore()
{
    QString string = gpib_->query(address_,"TEMP?").c_str();
    //QString = String den uns Ppms gibt
    auto list = string.split(',',QString::SkipEmptyParts);
    //nur die erste Zahl die herausgegebn wird ist für uns wichtig
    return QPair(list[0].toDouble(),list[1].toDouble());
}

QPair<double, double> PpmsInstrument::magFieldCore()
{
    QString string = gpib_->query(address_,"FIELD?").c_str();
    //QString = String den uns Ppms gibt
    auto list = string.split(',',QString::SkipEmptyParts);
    //nur die erste Zahl die herausgegebn wird ist für uns wichtig
    return QPair(list[0].toDouble(),list[1].toDouble());
}

double PpmsInstrument::angleCore()
{
    QString string = gpib_->query(address_,"MOVE?").c_str();
    //QString = String den uns Ppms gibt
    auto list = string.split(',',QString::SkipEmptyParts);
    //nur die erste Zahl die herausgegebn wird ist für uns wichtig
    return list[0].toDouble();
}

double PpmsInstrument::heliumCore()
{
    QString string = gpib_->query(address_,"LEVEL?").c_str();
    //QString = String den uns Ppms gibt
    auto list = string.split(',',QString::SkipEmptyParts);
    //nur die erste Zahl die herausgegebn wird ist für uns wichtig
    return list[0].toDouble();
}

std::string PpmsInstrument::ppmsStatus()
{

    return gpib_->query(address_, "GETDAT? 524295 1");
}

PpmsDataPoint PpmsInstrument::ppmsLogik()
{
    PpmsDataPoint ppmsDpoint;
    auto dataPoint =std::make_shared<DataPoint> ();
    ppmsDpoint.setPvTempLive(getLiveData()[0]);
    ppmsDpoint.setPvTempSetPoint(tempSetpointCore().first);
    ppmsDpoint.setPvTempRate(tempSetpointCore().second);

    ppmsDpoint.setPvMagFieldLive(getLiveData()[1]);
    ppmsDpoint.setPvMagSetPoint(magFieldCore().first);

    ppmsDpoint.setPvRotLive(getLiveData()[2]);
    ppmsDpoint.setPvRotSetPoint(angleCore());
    ppmsDpoint.setPvChamberLevel(heliumCore());
    ppmsDpoint.setPvSamplePressure(getLiveData()[3]);
    ppmsDpoint.setPvStatusPpms(ppmsStatus());

    return ppmsDpoint;
}

std::vector<double> PpmsInstrument::getLiveData()
{
    auto getdat=(QString::fromStdString(gpib_->query(address_,"GETDAT? 8912911 1")));
    //qDebug()<<getdat;
    auto Datavector = getdat.split(',');

    auto tempNow= Datavector[3];
    auto magFieldNow = Datavector[4];
    auto angleNow = Datavector[5];
    auto samplePressure = Datavector[6];
    //auto usertemp = Datavector[7];


    std::vector <double> liveData;

    liveData.push_back(tempNow.toDouble());
    liveData.push_back(magFieldNow.toDouble());
    liveData.push_back(angleNow.toDouble());
    liveData.push_back(samplePressure.toDouble());
    //liveData.push_back(usertemp.toDouble());


    return liveData;

}

void PpmsInstrument::openDevice()
{
    if (gpib_ == nullptr) {
        return;
    }
    qDebug()<<"openDevice";
    gpib_->openDevice(15);
    gpib_->cmd(address_,"USERTEMP 23 1.9 1.8 2 1");
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








