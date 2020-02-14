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
    , setPointStand(false)
    , startTemp_ (80)
    , endTemp_ (100)
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
    instrumentmanager_->setTempSetpoint(startTemp_, 1);
    }


}

void InduManager::onNewData(std::shared_ptr<DataPoint> datapoint)
{
    emit newData(datapoint);

    //TODO: startTemp und Endtemp mit gettern von Setpoint ersetzen!

    if(datapoint->pvTemp()==startTemp_&& setPointStand==false )
    {
        setPointStand =true;
        instrumentmanager_->setTempSetpoint(endTemp_,1);
    }


    if ((fw_ != nullptr) && (setPointStand==true))
    {
        fw_->append(datapoint);
    }

    if(datapoint->pvTemp()==endTemp_ && setPointStand==true)
    {
        setPointStand=false;
    }
}


