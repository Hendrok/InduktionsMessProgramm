#include "ppmsinstrument.h"
#include <memory>
#include <QDebug>

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
    Q_UNUSED(setpoint);
    Q_UNUSED(rate);
}

void PpmsInstrument::setMagFieldCore(double magField, double magRate)
{
    Q_UNUSED(magField);
    Q_UNUSED(magRate);
}

void PpmsInstrument::setAngleCore(double angle)
{
    Q_UNUSED(angle)
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








