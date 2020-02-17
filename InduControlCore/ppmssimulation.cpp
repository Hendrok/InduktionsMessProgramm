#include "ppmssimulation.h"
#include <QRandomGenerator>
#include <memory>
#include <QDebug>

#include "../InduCore/datapoint.h"
#include "instrumentmanager.h"

PpmsSimulation::PpmsSimulation()
     : datapoint_(DataPoint())
     , tempSetpoint_(300)
     , tempRate_(1)
     , measrunning_(false)
     , fieldSetpoint_(0)
     , fieldRate_(10)
     , ppmsHelium_(100)
     , tempNow_(300)

{
}

void PpmsSimulation::setTempSetpoint(double setpoint, double rate)
{
    tempSetpoint_ = setpoint;
    tempRate_ = rate;
}

void PpmsSimulation::SetMeasRunning(bool measrunning)
{
    measrunning_ =measrunning;
}

std::shared_ptr <DataPoint> PpmsSimulation::generateVariables()
{
    auto dataPoint =std::make_shared <DataPoint>();
    double test =QRandomGenerator::global()->bounded(1.0);
    ppmsHelium_ =QRandomGenerator::global()->bounded(1.0)+60;
    dataPoint->setpvPhase(test);
    dataPoint->setpvHeliumStatus(ppmsHelium_);
    dataPoint->setpvVolt(test);

    if(measrunning_==true)
    {
        dataPoint->setPvMeasurementOn(true);
    }
    if (measrunning_==false)
    {
        dataPoint->setPvMeasurementOn(false);
    }

    if (tempNow_< tempSetpoint_)
    {
        tempNow_= tempNow_ + tempRate_;
    }
    if (tempNow_> tempSetpoint_)
    {
        tempNow_=tempNow_-tempRate_;
    }



    dataPoint->setpvTemp(tempNow_);





    qDebug()<<tempNow_;

    return dataPoint;

}
