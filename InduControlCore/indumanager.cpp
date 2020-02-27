#include "indumanager.h"
#include <QDebug>
#include <vector>

//Internal Classes
#include "instrumentmanager.h"
#include "../InduCore/measurementsequence.h"
#include "../InduCore/measseqtc.h"
#include "../InduCore/measseqjc.h"
#include "../InduCore/datapoint.h"
#include "../InduCore/filewriter.h"
#include "../Instruments/ppmsdatapoint.h"



InduManager::InduManager()
    : measurementNumber_(0)
    , instrumentmanager_ (std::make_unique<InstrumentManager>())
    , fw_(nullptr)
    , mSeqTc_(std::make_shared<MeasSeqTc>())
    , mSeqJc_(std::make_shared<MeasSeqJc>())
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
    for (const auto mesSeq: mVecSeq)
    {
        mVecSeq_.push_back(mesSeq);
    }

    if(measurementState == State::Idle){
        measurementState = State::CheckForMeas;
        emit newState(measurementState);
    }
}

void InduManager::startMeasurement(std::shared_ptr<const MeasurementSequence> measurementSequence)
{
    auto seqTc = std::dynamic_pointer_cast<const MeasSeqTc> (measurementSequence);
    auto seqJc = std::dynamic_pointer_cast<const MeasSeqJc> (measurementSequence);
    fw_= std::make_unique<FileWriter>();
    fw_->openFile(measurementSequence);
    if(seqTc != nullptr){
        mSeqTc_->setTempStart(seqTc->tempStart());
        mSeqTc_->setTempEnd(seqTc->tempEnd());
        mSeqTc_->setTemperatureRate(seqTc->temperatureRate());
        mSeqTc_->setVoltageAmplitude(seqTc->voltageAmplitude());
        instrumentmanager_->setTempSetpoint(mSeqTc_->tempStart(), mSeqTc_->temperatureRate());
        measurementState = State::ApproachStartTc;
        emit newState(measurementState);
    }
    if(seqJc != nullptr){
        mSeqJc_->setVoltStart(seqJc->voltStart());
        mSeqJc_->setVoltRate(seqJc->voltRate());
        mSeqJc_->setVoltEnd(seqJc->voltEnd());
        mSeqJc_->setTemperature(seqJc->temperature());
        instrumentmanager_->setTempSetpoint(mSeqJc_->temperature(), 10);
        measurementState = State::ApproachStartJc;
        emit newState(measurementState);
    }
}
void InduManager::onNewData(std::shared_ptr<DataPoint> datapoint)
{
    emit newData(datapoint);

    switch (measurementState)
    {
        case State::Idle:{
                /*NOTE
                 * if abfrage-> ob das Programm bei Aktueller Temp bleiben soll, oder Energiesparmodus!
                */
                break;
            }
    //Tc
        case State::ApproachStartTc:{
                if(std::abs(mSeqTc_->tempStart() - datapoint->ppmsdata()->pvTempLive()) < 0.1)
                {
                    measurementState = State::ApproachEndTc;
                    instrumentmanager_->setTempSetpoint(mSeqTc_->tempEnd(), mSeqTc_->temperatureRate());
                    instrumentmanager_->SetInputVoltage(mSeqTc_->voltageAmplitude());
                }
                break;
            }
        case State::ApproachEndTc:{
               if(fw_!= nullptr){
                    fw_->MeasurementState(measurementState);
                    fw_->append(datapoint);
               }

               if(std::abs(mSeqTc_->tempEnd() - datapoint->ppmsdata()->pvTempLive()) < 0.1)
               {
                    fw_->closeFile();
                    measurementState = State::CheckForMeas;
                    measurementNumber_++;
               }
                break;
            }
    //Jc
        case State::ApproachStartJc:{
                if(std::abs(mSeqJc_->temperature() - datapoint->ppmsdata()->pvTempLive()) < 0.1)
                {
                    measurementState = State::ApproachEndJc;
                    instrumentmanager_->SetInputVoltage(mSeqJc_->voltStart());
                }
                break;
        }

        case State::ApproachEndJc:{
            if (datapoint->lockindata()->pvVoltLive() < mSeqJc_->voltEnd())
            {
                instrumentmanager_->SetInputVoltage(datapoint->lockindata()->pvVoltLive() + mSeqJc_->voltRate());
            }
            if (datapoint->lockindata()->pvVoltLive() > mSeqJc_->voltEnd())
            {
                instrumentmanager_->SetInputVoltage(datapoint->lockindata()->pvVoltLive() - mSeqJc_->voltRate());
            }
            //slow approach
            if(std::abs(mSeqJc_->voltEnd() - datapoint->lockindata()->pvVoltLive()) < mSeqJc_->voltRate())
            {
                mSeqJc_->setVoltRate(0.01);
            }

            if(fw_!= nullptr){
                    fw_->MeasurementState(measurementState);
                    fw_->append(datapoint);
            }
            if(std::abs(mSeqJc_->voltEnd() - datapoint->lockindata()->pvVoltLive()) < 0.01){
                fw_->closeFile();
                measurementState = State::CheckForMeas;
                measurementNumber_++;
            }

            break;
        }

        case State::CheckForMeas:{
                if(mVecSeq_.size()> measurementNumber_ )
                {
                    emit startNewMeasurement(mVecSeq_[measurementNumber_]);
                }
                else{
                    measurementState = State::Idle;
                }
                break;
            }

        default:assert(false);
    }

    emit newState(measurementState);
}


