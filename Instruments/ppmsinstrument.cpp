#include "ppmsinstrument.h"
#include <memory>
#include <QDebug>
#include <string>
#include <QPair>
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
    QPair<std::string, std::string> setTempSetpointStr =
            QPair(dtoStr(setpoint), dtoStr(rate));
}

void PpmsInstrument::setMagFieldCore(double magField, double magRate)
{
    QPair<std::string, std::string> setMagFieldStr =
            QPair(dtoStr(magField), dtoStr(magRate));
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

std::string PpmsInstrument::dtoStr(double number)
{
    return std::to_string(number);
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








