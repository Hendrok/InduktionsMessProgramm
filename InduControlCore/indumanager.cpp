#include "indumanager.h"
#include <QDebug>
#include <memory>
#include <vector>
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
    //, mVecSeq_ (std::vector <std::make_shared<MeasurementSequence>>()) // wie geht dieses
    , instrumentmanager_ (std::make_unique<InstrumentManager>())
    , fw_(nullptr)
    , mSeqTc_(std::make_shared <MeasSeqTc>())
    , measurementState(State::Idle)


{
    connect(instrumentmanager_.get(), &InstrumentManager::newData,
                this, &InduManager::onNewData);
}

InduManager::~InduManager()
{
}

void InduManager::appendMeasurement(std::vector<std::shared_ptr<const MeasurementSequence> > mVecSeq)
{
    mVecSeq_=mVecSeq;
}

void InduManager::checkStartMeasurement()
{
    if(mVecSeq_[measurementNumber_]!=nullptr && measurementState == State::Idle)
    {
        emit startNewMeasurement(mVecSeq_[measurementNumber_]);
    }
}


void InduManager::startMeasurement(std::shared_ptr<const MeasurementSequence> measurementSequence)
{

    auto seqTc = std::dynamic_pointer_cast <const MeasSeqTc> (mVecSeq_[measurementNumber_]);
    fw_= std::make_unique<FileWriter>();

    fw_->openFile(mVecSeq_[measurementNumber_]);
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
        measurementState = State::Idle;

        measurementNumber_++;   //starte neue Messung
    }

}

InduManager::State InduManager::getMeasurementState() const
{
    return measurementState;
}


