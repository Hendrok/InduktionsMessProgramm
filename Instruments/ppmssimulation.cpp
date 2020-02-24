#include "ppmssimulation.h"
#include <QRandomGenerator>
#include <memory>
#include <QDebug>

#include "../InduCore/datapoint.h"
#include "../InduControlCore/instrumentmanager.h"
#include "../Instruments/ppmsdatapoint.h"
#include "../Instruments/lockindatapoint.h"

/* WARNING
* hier initialisierst du measrunning_ mit false, obwohl das eine variable vom typ double ist.
* Frage: brauchst du die hier überhaupt, oder ist das alter Kram?
*/
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


std::shared_ptr <DataPoint> PpmsSimulation::generateVariablesTc()
{
    PpmsDataPoint ppmsDpoint;
    LockInDataPoint lockingDpoint;

    auto dataPoint =std::make_shared <DataPoint>();
    double test =QRandomGenerator::global()->bounded(1.0);

    ppmsDpoint.setPvTempSetPoint(tempSetpoint_);
    ppmsDpoint.setPvTempRate(tempRate_);
    ppmsDpoint.setPvVoltLive(test);
    lockingDpoint.setPvPhase(test);




    if (tempNow_< tempSetpoint_)
    {
        tempNow_= tempNow_ + tempRate_;
    }
    if (tempNow_> tempSetpoint_)
    {
        tempNow_=tempNow_-tempRate_;
    }

    ppmsDpoint.setPvTempLive(tempNow_);

    dataPoint->setPpmsdata(std::make_shared<const PpmsDataPoint> (ppmsDpoint));
    dataPoint->setLockindata(std::make_shared<const LockInDataPoint> (lockingDpoint));
    return dataPoint;

}
