#include "instrumentmanager.h"
#include <QDebug>
#include <QRandomGenerator>


#include "../InduCore/datapoint.h"

InstrumentManager::InstrumentManager(std::shared_ptr<MeasurementSequence> measurementSequence)
    : timer_(new QTimer(this))
{
    starttemp_=measurementSequence->tempStart();
    endtemp_=measurementSequence->tempEnd();
    currenttemp_=starttemp_;

    connect(timer_, &QTimer::timeout, this, &InstrumentManager::createRandomDataPoints);
    timer_->start(2000);

}
InstrumentManager::~InstrumentManager()
{

}
//void InstrumentManager::creatingRandomDataPoint(std::shared_ptr<MeasurementSequence> measurementSequence,std::shared_ptr<DataPoint> datapoint)

void InstrumentManager::createRandomDataPoints(/*std::shared_ptr<MeasurementSequence> measurementSequence*/)
{
    auto datapoint =std::make_shared <DataPoint>();

    datapoint->setpvTemp(currenttemp_);
    currenttemp_=currenttemp_ +0.1;
    double test =QRandomGenerator::global()->bounded(1.0);
    datapoint->setpvVolt(test);
    qDebug()<<currenttemp_;
    qDebug()<<test;
    if(currenttemp_==100)//measurementSequence->tempEnd())
    {
        timer_->stop();
    }

    emit newData(datapoint);


}
