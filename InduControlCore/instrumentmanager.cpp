#include "instrumentmanager.h"
#include <QDebug>
#include <QRandomGenerator>


#include "../InduCore/datapoint.h"

InstrumentManager::InstrumentManager()
    : timer_(new QTimer(this))
     ,starttemp_(80)
     ,currenttemp_(starttemp_)
     ,endtemp_(100)
{


    connect(timer_, &QTimer::timeout, this, &InstrumentManager::onPolling);
    timer_->start(200);

}
InstrumentManager::~InstrumentManager()
{

}


void InstrumentManager::onPolling()
{
    auto dataPoint =std::make_shared <DataPoint>();
    double test =QRandomGenerator::global()->bounded(1.0);
    dataPoint->setpvVolt(test);

    dataPoint->setpvTemp(currenttemp_);
    currenttemp_=currenttemp_+1;

    dataPoint->setpvPhase(test);
    qDebug()<<test;
    if(currenttemp_>endtemp_){
       timer_->stop();
    }

    emit newData(dataPoint);


}
