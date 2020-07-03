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
#include <QThread>


InduManager::InduManager()
    : measurementNumber_(0)
    , instrumentmanager_(std::make_unique<InstrumentManager>())
    , fw_(nullptr)
    , mSeqTc_(std::make_shared<MeasSeqTc>())
    , mSeqJc_(std::make_shared<MeasSeqJc>())
    , measurementState(State::Idle)
    , magFieldSP_(0)
    , angleSP_(0)
{   
    connect(instrumentmanager_.get(), &InstrumentManager::newData,
            this, &InduManager::onNewData);
    connect(instrumentmanager_.get(), &InstrumentManager::newTempSP,
            this, &InduManager::onNewTempSP);
    connect(instrumentmanager_.get(), &InstrumentManager::newMagSP,
            this, &InduManager::onNewMagSP);
    connect(instrumentmanager_.get(), &InstrumentManager::newAngleSP,
            this, &InduManager::onNewAngleSP);
    connect(instrumentmanager_.get(), &InstrumentManager::newFreqSP,
            this, &InduManager::onNewFreqSP);
    connect(instrumentmanager_.get(), &InstrumentManager::newSensivitySP,
            this, &InduManager::onNewSensivitySP);
    connect(instrumentmanager_.get(), &InstrumentManager::newHarmonicSP,
            this, &InduManager::onNewHarmonicSP);
    connect(instrumentmanager_.get(), &InstrumentManager::newErrorMessageMag,
            this, &InduManager::onNewErrorMessageMag);
    connect(instrumentmanager_.get(), &InstrumentManager::newErrorMessageHel,
            this, &InduManager::onNewErrorMessageHel);
    connect(instrumentmanager_.get(), &InstrumentManager::newErrorMessagePpms,
            this, &InduManager::onNewErrorMessagePpms);
}

InduManager::~InduManager()
{
}


void InduManager::appendMeasurement(std::vector<std::shared_ptr<const MeasurementSequence>> mVecSeq)
{
    for (const auto &mesSeq: mVecSeq){
        mVecSeq_.push_back(mesSeq);
    }

    if(measurementState == State::Idle){
        measurementState = State::CheckForMeas;
        emit newState(measurementState);
    }
}


void InduManager::startMeasurement(std::shared_ptr<const MeasurementSequence> measurementSequence)
{
    auto seqTc = std::dynamic_pointer_cast<const MeasSeqTc>(measurementSequence);
    auto seqJc = std::dynamic_pointer_cast<const MeasSeqJc>(measurementSequence);
    fw_= std::make_unique<FileWriter>();
    fw_->openFile(measurementSequence);
    if(seqTc != nullptr){
        mSeqTc_->setTempStart(seqTc->tempStart());
        mSeqTc_->setTempEnd(seqTc->tempEnd());
        mSeqTc_->setTemperatureRate(seqTc->temperatureRate());
        mSeqTc_->setVoltageAmplitude(seqTc->voltageAmplitude());
        instrumentmanager_->setTempSetpoint(mSeqTc_->tempStart(),20);
        measurementState = State::ApproachStartTc;
        emit newState(measurementState);
    }
    if(seqJc != nullptr){
        mSeqJc_->setVoltStart(seqJc->voltStart());
        mSeqJc_->setVoltRate(seqJc->voltRate());
        mSeqJc_->setVoltEnd(seqJc->voltEnd());
        mSeqJc_->setTemperature(seqJc->temperature());
        instrumentmanager_->setTempSetpoint(mSeqJc_->temperature(), 20);
        measurementState = State::ApproachStartJc;
        emit newState(measurementState);
    }

    instrumentmanager_->setAngle(measurementSequence->coilAngle());
    instrumentmanager_->setMagFieldSP(measurementSequence->magneticField(), 200);
    instrumentmanager_->setHarmonic(measurementSequence->harmonicWave());
    instrumentmanager_->setFrequency(measurementSequence->frequency());
}

void InduManager::onNewData(std::shared_ptr<DataPoint> datapoint)
{
    emit newData(datapoint);

    //ppmsStatus
    QString ppmsStatusStr = QString::fromStdString(datapoint->ppmsdata()->pvStatusPpms());
    auto ppmsStatus = ppmsStatusStr.toDouble();
    bool tempStable = false;
    bool magStable = false;
    bool rotStable = false;
    if ((static_cast<int>(ppmsStatus) & 0b1111) == 1) { tempStable = true ; }
    if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 1) { magStable = true ; }
    if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 1) { rotStable = true ; }
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
                if( std::abs(mSeqTc_->tempStart() - datapoint->ppmsdata()->pvTempLive()) < 0.7 &&
                        std::abs(magFieldSP_ - datapoint->ppmsdata()->pvMagFieldLive()) < 10 &&
                        std::abs(angleSP_ - datapoint->ppmsdata()->pvRotLive()) < 3 &&
                        tempStable == true &&
                        magStable == true &&
                        rotStable == true)
                {
                    measurementState = State::ApproachEndTc;
                    instrumentmanager_->setTempSetpoint(mSeqTc_->tempEnd(), mSeqTc_->temperatureRate());
                    instrumentmanager_->setInputVoltage(mSeqTc_->voltageAmplitude());
                    emit newState(measurementState);
                }
                break;
            }
        case State::ApproachEndTc:{
               if(fw_!= nullptr){
                    fw_->MeasurementState(measurementState);
                    fw_->append(datapoint);
               }

               if(std::abs(mSeqTc_->tempEnd() - datapoint->ppmsdata()->pvTempLive()) < 0.6 &&
                       tempStable == true)
               {
                    fw_->closeFile();
                    measurementState = State::CheckForMeas;
                    measurementNumber_++;
                    emit newState(measurementState);
               }
                break;
            }
    //Jc
        case State::ApproachStartJc:{
                if( std::abs(mSeqJc_->temperature() - datapoint->ppmsdata()->pvTempLive()) < 0.6 &&
                        std::abs(magFieldSP_ - datapoint->ppmsdata()->pvMagFieldLive()) < 10 &&
                        std::abs(angleSP_ - datapoint->ppmsdata()->pvRotLive()) < 1 &&
                        tempStable == true &&
                        magStable == true &&
                        rotStable == true)
                {
                    measurementState = State::ApproachEndJc;
                    instrumentmanager_->setInputVoltage(mSeqJc_->voltStart());
                    emit newState(measurementState);
                }
                break;
        }

        case State::ApproachEndJc:{
            if (datapoint->lockindata()->pvVoltInputLive() < mSeqJc_->voltEnd())
            {
                instrumentmanager_->setInputVoltage(datapoint->lockindata()->pvVoltInputLive() + mSeqJc_->voltRate());   
            }
            if (datapoint->lockindata()->pvVoltInputLive() > mSeqJc_->voltEnd())
            {

                instrumentmanager_->setInputVoltage(datapoint->lockindata()->pvVoltInputLive() - mSeqJc_->voltRate());
            }
            //slow approach
            /*if(std::abs(mSeqJc_->voltEnd() - datapoint->lockindata()->pvVoltInputLive()) < mSeqJc_->voltRate())
            {
                mSeqJc_->setVoltRate(0.01);
            }*/

            if(fw_!= nullptr){
                    fw_->MeasurementState(measurementState);
                    fw_->append(datapoint);
            }
            if(std::abs(mSeqJc_->voltEnd() - datapoint->lockindata()->pvVoltInputLive()) < 0.01){
                fw_->closeFile();
                measurementState = State::CheckForMeas;
                measurementNumber_++;
                emit newState(measurementState);
            }

            break;
        }

        case State::CheckForMeas:{
                if(mVecSeq_.size()> measurementNumber_ )
                {
                    emit startNewMeasurement(mVecSeq_[measurementNumber_]);
                    startMeasurement(mVecSeq_[measurementNumber_]);
                }
                else{
                    measurementState = State::Idle;
                    emit newState(measurementState);
                }
                break;
            }

        default:assert(false);
    }
}

void InduManager::onNewTempSP(double setpoint, double rate)
{
    emit newTempSP(setpoint, rate);

}

void InduManager::onNewMagSP(double magField, double magRate)
{
    emit newMagSP(magField,magRate);
    magFieldSP_ = magField;
}

void InduManager::onNewAngleSP(double angle)
{
    emit newAngleSP(angle);
    angleSP_ = angle;
}

void InduManager::onNewFreqSP(double freq)
{
    emit newFreqSP(freq);
}

void InduManager::onNewSensivitySP(int sensivity)
{
    emit newSensivitySP(sensivity);
}

void InduManager::onNewHarmonicSP(int harmonicW)
{
    emit newHarmonicSP(harmonicW);
}

void InduManager::onNewErrorMessageMag(QString errorMag)
{
    emit newErrorMessageMag(errorMag);
}

void InduManager::onNewErrorMessageHel(QString errorHel)
{
    emit newErrorMessageHel(errorHel);
}

void InduManager::onNewErrorMessagePpms(QString errormessagePpms)
{
    emit newErrorMessagePpms(errormessagePpms);
}

