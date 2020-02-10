#include "instrumentmanager.h"
#include <QDebug>
#include <QRandomGenerator>


#include "../InduCore/datapoint.h"
#include "ppmssimulation.h"

InstrumentManager::InstrumentManager()
    : timer_(new QTimer(this))
    , ppmssimu_(new PpmsSimulation())
{


    connect(timer_, &QTimer::timeout, this, &InstrumentManager::onPolling);
    timer_->start(200);

}
InstrumentManager::~InstrumentManager()
{
    timer_->stop();
}


void InstrumentManager::onPolling()
{

    auto dataPoint = ppmssimu_->generateVariables();



    emit newData(dataPoint);


}
