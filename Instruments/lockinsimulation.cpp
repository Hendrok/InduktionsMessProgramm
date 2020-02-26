#include "lockinsimulation.h"
#include <QRandomGenerator>
#include <memory>
#include <QDebug>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "../InduControlCore/instrumentmanager.h"
#include "../Instruments/ppmsdatapoint.h"
#include "../Instruments/lockindatapoint.h"

LockInSimulation::LockInSimulation()
    : datapoint_(DataPoint())
    , inputVoltage_ (0.1)
    , voltnow_(0.1)
{  
}

void LockInSimulation::SetInputVoltage(double InputVoltage)
{
    inputVoltage_ = InputVoltage;
}



std::shared_ptr<DataPoint> LockInSimulation::lockInLogik()
{
    LockInDataPoint lockingDpoint;

    auto dataPoint =std::make_shared<DataPoint> ();
    double test =QRandomGenerator::global()->bounded(1.0)+90;

    lockingDpoint.setPvPhase(test);
    lockingDpoint.setPvVoltLive(inputVoltage_);

    dataPoint->setLockindata(std::make_shared<const LockInDataPoint> (lockingDpoint));
    return dataPoint;

}
