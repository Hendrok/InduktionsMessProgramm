#include "instrumentmanager.h"
#include <QDebug>
#include <QRandomGenerator>


#include "../InduCore/datapoint.h"
#include "../Instruments/ppmssimulation.h"

InstrumentManager::InstrumentManager()
    : timer_(new QTimer(this))
    , ppmssimu_(new PpmsSimulation())
{


    connect(timer_, &QTimer::timeout, this, &InstrumentManager::onPolling);
    timer_->start(200);


}
InstrumentManager::~InstrumentManager()
{
  /* BUG
   * Wenn du PPMSSimulation als rohen Pointer erstellst, musst du ihn hier deleten
   */
}

void InstrumentManager::setTempSetpoint(double setpoint, double rate)
{
    ppmssimu_->setTempSetpoint(setpoint, rate);
}


void InstrumentManager::onPolling()
{

    auto dataPoint = ppmssimu_->generateVariablesTc();



    emit newData(dataPoint);


}
