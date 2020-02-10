#include "ppmssimulation.h"
#include <QRandomGenerator>
#include <memory>
#include <QDebug>

#include "../InduCore/datapoint.h"
#include "instrumentmanager.h"
#include "../InduCore/measurementsequence.h"

PpmsSimulation::PpmsSimulation()
     :starttemp_(80)
     ,currenttemp_(starttemp_)
     ,endtemp_(100)
{
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


    return dataPoint;

}

void PpmsSimulation::getStartwerte(std::shared_ptr<MeasurementSequence> &measurementSequence)
{

    starttemp_=measurementSequence->tempStart();
    currenttemp_=starttemp_;
    endtemp_=measurementSequence->tempEnd();
}
