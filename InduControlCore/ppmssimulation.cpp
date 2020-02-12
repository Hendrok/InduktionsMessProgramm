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
     , tempRate_(1)
     , fieldSetpoint_(0)
     , fieldRate_(10)
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

    dataPoint->setpvTemp(tempSetpoint_);
    tempSetpoint_=tempSetpoint_+1;

    dataPoint->setpvPhase(test);
    qDebug()<<test;

    return dataPoint;

}
