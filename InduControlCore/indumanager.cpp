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
#include "../Instruments/ppmsdatapoint.h"
InduManager::InduManager()
    : measurementNumber_(0)
    , instrumentmanager_(std::make_unique<InstrumentManager>())
    , fw_(nullptr)
    , mSeq_(std::make_shared <MeasurementSequence>())
    , measurementState(State::Idle)


{
    connect(instrumentmanager_.get(), &InstrumentManager::newData,
                this, &InduManager::onNewData);
}

InduManager::~InduManager()
{
}

void InduManager::startMeasurement(std::shared_ptr<const MeasurementSequence> measurementSequence)
{
    auto seqTc = std::dynamic_pointer_cast <const MeasSeqTc> (measurementSequence);
    auto mSeqTc_ = std::dynamic_pointer_cast <MeasSeqTc> (mSeq_);
    fw_= std::make_unique<FileWriter>();
    fw_->openFile(measurementSequence);
    if(seqTc !=nullptr){
        mSeqTc_->setTempStart(seqTc->tempStart());
        mSeqTc_->setTempEnd(seqTc->tempEnd());
        mSeqTc_->setTemperatureRate(seqTc->temperatureRate());
        instrumentmanager_->setTempSetpoint(mSeqTc_->tempStart(), mSeqTc_->temperatureRate());
        measurementState= State::ApproachStart;
    }
}


void InduManager::onNewData(std::shared_ptr<DataPoint> datapoint)
{
    emit newData(datapoint);

    auto mSeqTc_ = std::dynamic_pointer_cast <MeasSeqTc> (mSeq_);

    if(measurementState== State::ApproachStart && std::abs(mSeqTc_->tempStart() - datapoint->ppmsdata()->pvTempLive()) < mSeqTc_->temperatureRate())
    {
        measurementState = State::ApproachEnd;
        instrumentmanager_->setTempSetpoint(mSeqTc_->tempEnd(), mSeqTc_->temperatureRate());
        fw_->append(datapoint);
    }

    if ((fw_ != nullptr) && (measurementState==State::ApproachEnd))
    {
        fw_->append(datapoint);
    }


    if( (measurementState==State::ApproachEnd) && std::abs(mSeqTc_->tempEnd() - datapoint->ppmsdata()->pvTempLive()) < mSeqTc_->temperatureRate())
    {

        measurementState= State::Idle;
    }

}

InduManager::State InduManager::getMeasurementState() const
{
    return measurementState;
}


