#include "ppmssimulation.h"
#include <QRandomGenerator>
#include <memory>
#include <QDebug>

#include "../InduCore/datapoint.h"
#include "instrumentmanager.h"
#include "../InduCore/measurementsequence.h"

PpmsSimulation::PpmsSimulation()
     :datapoint_(DataPoint())
     , tempSetpoint_(300)
     , tempRate_(10)
     , fieldSetpoint_(0)
     , fieldRate_(10)
     , starttemp_(80)
     , currenttemp_(starttemp_)
     , endtemp_(100)
{
}

void PpmsSimulation::setTempSetpoint(double setpoint, double rate)
{
    tempSetpoint_ = setpoint;
        tempRate_ = rate;
}

std::shared_ptr <DataPoint> PpmsSimulation::generateVariables()
{
    auto dataPoint =std::make_shared <DataPoint>();
    double test =QRandomGenerator::global()->bounded(1.0);
    dataPoint->setpvVolt(test);

    dataPoint->setpvTemp(currenttemp_);
    currenttemp_=currenttemp_+1;

    dataPoint->setpvPhase(test);
    qDebug()<<test;
    /*if(currenttemp_>endtemp_+1)
    {
        InstrumentManager Im;
        Im.~InstrumentManager();
    }*/

    return dataPoint;

}

void PpmsSimulation::getStartwerte(std::shared_ptr<MeasurementSequence> &measurementSequence)
{
    starttemp_=measurementSequence->tempStart();
    currenttemp_=starttemp_;
    endtemp_=measurementSequence->tempEnd();
}
