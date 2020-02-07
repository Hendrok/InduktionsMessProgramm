#include "instrumentmanager.h"
#include <QDebug>
#include <QRandomGenerator>


#include "../InduCore/datapoint.h"

InstrumentManager::InstrumentManager()
    : timer_(new QTimer(this))
{


    connect(timer_, &QTimer::timeout, this, &InstrumentManager::onPolling);
    timer_->start(2000);

}
InstrumentManager::~InstrumentManager()
{

}


void InstrumentManager::onPolling()
{
    auto dataPoint =std::make_shared <DataPoint>();
    double test =QRandomGenerator::global()->bounded(1.0);
    dataPoint->setpvVolt(test);
    dataPoint->setpvTemp(test);
    dataPoint->setpvPhase(test);
    qDebug()<<test;


    emit newData(dataPoint);


}
