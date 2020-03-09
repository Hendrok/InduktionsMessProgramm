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

PpmsInstrument::PpmsInstrument()
    : datapoint_(DataPoint())
    , tempSetpoint_(300)
    , tempRate_(10)
    , fieldSetpoint_(0)
    , fieldRate_(10)
    , ppmsHelium_(100)
    , tempNow_(300)
    , magField_(0)
    , angle_(0)
{   
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
}

void PpmsInstrument::setMagFieldCore(double magField, double magRate)
{
    //TODO: Abfrage MagField, spezifisch für 9/14 T!
    //transform to oe
    magField = magField *10;
    magRate = magRate *10;
    std::string setMagFieldStr= dtoStr(magField, 0) + " " + dtoStr(magRate, 0);
}

void PpmsInstrument::setAngleCore(double angle)
{
    std::string angleStr = itoStr(angle);
}

QPair<double, double> PpmsInstrument::tempSetpointCore()
{
    return QPair(0,0);
}

QPair<double, double> PpmsInstrument::magFieldCore()
{
    return QPair(0,0);
}

double PpmsInstrument::angleCore()
{
    return 0;
}

std::string PpmsInstrument::dtoStr(double number,int dec)
{
    std::stringstream sstring;
    sstring << std::fixed << std::setprecision(dec) << number;
    return sstring.str();
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








