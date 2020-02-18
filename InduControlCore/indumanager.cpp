#include "indumanager.h"
#include <QDebug>
#include <memory>
//Eigene Klassen
#include "instrumentmanager.h"
#include "ppmssimulation.h"
#include "../InduCore/measurementsequence.h"
#include "../InduCore/measseqtc.h"
#include "../InduCore/datapoint.h"
#include "../InduCore/filewriter.h"

InduManager::InduManager()
    : measurementState(idle)
    , instrumentmanager_(new InstrumentManager())
    , fw_(nullptr)
    , mSeqTc_(std::make_shared <MeasSeqTc>())


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
        mSeqTc_->setTempStart(seqTc->tempStart());
        mSeqTc_->setTempEnd(seqTc->tempEnd());
        mSeqTc_->setTemperatureRate(seqTc->temperatureRate());
        instrumentmanager_->setTempSetpoint(mSeqTc_->tempStart(), mSeqTc_->temperatureRate());
    }
}


std::shared_ptr<DataPoint> InduManager::onNewData(std::shared_ptr<DataPoint> datapoint)
{
    emit newData(datapoint);


    if(datapoint->pvMeasurementOn()==false && std::abs(mSeqTc_->tempStart() - datapoint->pvTemp()) < mSeqTc_->temperatureRate())
    {
        instrumentmanager_->SetMeasRunning(true);
        instrumentmanager_->setTempSetpoint(mSeqTc_->tempEnd(), mSeqTc_->temperatureRate());
        fw_->append(datapoint);
    }

    if ((fw_ != nullptr) && (datapoint->pvMeasurementOn()==true))
    {
        fw_->append(datapoint);
    }

    qDebug()<<datapoint->pvMeasurementOn();

    if(datapoint->pvTemp()==mSeqTc_->tempEnd() && (datapoint->pvMeasurementOn()==true))
    {

        instrumentmanager_->SetMeasRunning(false);
    }


    return  datapoint;
}


