#include "indumanager.h"
#include <QDebug>
#include <memory>
//Eigene Klassen
#include "instrumentmanager.h"
#include "ppmssimulation.h"
#include "../InduCore/measurementsequence.h"
#include "../InduCore/MeasSeqTc.h"
#include "../InduCore/datapoint.h"
#include "../InduCore/filewriter.h"

InduManager::InduManager()
    : instrumentmanager_(new InstrumentManager())
    , fw_(nullptr)
    , startTemp_ (80)
    , endTemp_ (100)
    , temprate_ (20)
{
    connect(instrumentmanager_, &InstrumentManager::newData,
                this, &InduManager::onNewData);
}

InduManager::~InduManager()
{
    delete instrumentmanager_;
}

void InduManager::startMeasurement(std::shared_ptr<const MeasurementSequence> &measurementSequence)
{
    auto seqTc = std::dynamic_pointer_cast <const MeasSeqTc> (measurementSequence);

    fw_= std::make_unique<FileWriter>();
    fw_->openFile(measurementSequence);
    if(seqTc !=nullptr){
        startTemp_ = seqTc->tempStart();
        endTemp_ = seqTc->tempEnd();
        temprate_ = seqTc->temperatureRate();
        instrumentmanager_->setTempSetpoint(startTemp_, temprate_);
    }


}

std::shared_ptr<DataPoint> InduManager::onNewData(std::shared_ptr<DataPoint> datapoint)
{
    emit newData(datapoint);


    if(datapoint->pvMeasurementOn()==false && std::abs(startTemp_ - datapoint->pvTemp()) < temprate_)
    {
        instrumentmanager_->SetMeasRunning(true);
        instrumentmanager_->setTempSetpoint(endTemp_, temprate_);
        fw_->append(datapoint);
    }

    if ((fw_ != nullptr) && (datapoint->pvMeasurementOn()==true))
    {
        fw_->append(datapoint);
    }

    qDebug()<<datapoint->pvMeasurementOn();

    if(datapoint->pvTemp()==endTemp_ && (datapoint->pvMeasurementOn()==true))
    {

        instrumentmanager_->SetMeasRunning(false);
    }


    return  datapoint;
}


