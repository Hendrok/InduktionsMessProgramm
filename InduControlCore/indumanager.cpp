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
    :instrumentmanager_(new InstrumentManager())
    ,fw_(nullptr)
    , setPointStand(false)
{
    connect(instrumentmanager_, &InstrumentManager::newData,
                this, &InduManager::onNewData);
}

InduManager::~InduManager()
{
    delete instrumentmanager_;
}

void InduManager::startMeasurement(std::shared_ptr<const MeasSeqTc> &measurementSequence)
{
    fw_= std::make_unique<FileWriter>();
    fw_->openFile(measurementSequence);
    instrumentmanager_->setTempSetpoint(measurementSequence->tempStart(), 1);


}

void InduManager::onNewData(std::shared_ptr<DataPoint> datapoint)
{
    emit newData(datapoint);


    if(datapoint->pvTemp()==80&& setPointStand==false )
    {
        setPointStand =true;
    }


    if ((fw_ != nullptr) && (setPointStand==true))
    {
        fw_->append(datapoint);
    }

    if(datapoint->pvTemp()==100 && setPointStand==true)
    {
        setPointStand=false;
    }
}


