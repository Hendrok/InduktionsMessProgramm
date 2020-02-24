#include "indumanager.h"
#include <QDebug>
#include <memory>
#include <vector>
//Eigene Klassen
#include "instrumentmanager.h"
#include "../Instruments/ppmssimulation.h"
#include "../InduCore/measurementsequence.h"
#include "../InduCore/measseqtc.h"
#include "../InduCore/datapoint.h"
#include "../InduCore/filewriter.h"
#include "../Instruments/ppmsdatapoint.h"
InduManager::InduManager()
    : measurementNumber_(0)
    //, mVecSeq_ (std::vector <std::make_shared<const MeasurementSequence>>()) // wie geht dieses
    , instrumentmanager_ (std::make_unique<InstrumentManager>())
    , fw_(nullptr)
    , mSeqTc_(std::make_shared <MeasSeqTc>())
    , measurementState(State::Idle)


{
    connect(instrumentmanager_.get(), &InstrumentManager::newData,
                this, &InduManager::onNewData);
    //mVecSeq_ = std::vector<std::make_shared<MeasurementSequence>>();  // diese nicht gut
}

InduManager::~InduManager()
{
  /* NOTE
   * der leere Deconstructor kann hier und in der Header-Datei weg, du machst
   * hier eh nix
   */
}

void InduManager::appendMeasurement(std::vector<std::shared_ptr<const MeasurementSequence> > mVecSeq)
{
    /* BUG
     * du vergleichst hier unsigned mit size_t (der Typ, der von der Methode size()
     * zurückgegegen wird.
     * Das mag auf 32-Bit-System funktionieren, spätestens auf 64-Bit-Architekturen ist es
     * ein Bug, da sizeof(unsigned int) != sizeof(size_t)
     *
     * Besser: Immer range-basierte for-Schleifen verwenden, damit solche subtilen Bugs erst
     * gar nicht auftauchen.
     *
     * Beispiel:
     * for (const auto& element : mVecSeg)
     * {
     *    mVecSeg_.push_back(element);
     * }
     */
    for (unsigned i=0; i< mVecSeq.size();i++)
    {
        mVecSeq_.push_back(mVecSeq[i]);
    }
}

void InduManager::checkStartMeasurement()
{
    if(mVecSeq_.size()> measurementNumber_ && measurementState == State::Idle)
    {
        emit startNewMeasurement(mVecSeq_[measurementNumber_]);
    }
}


void InduManager::startMeasurement(std::shared_ptr<const MeasurementSequence> measurementSequence)
{

    auto seqTc = std::dynamic_pointer_cast <const MeasSeqTc> (measurementSequence);
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
    /* BUG
     * der Fehler liegt hier, dass du keine break-Befehle verwendest. Switch-Statements gehen so:
     *
     * switch (value)
     * {
     *   case A:
     *   {
     *     ...
     *     break;
     *   }
     *   case B:
     *   {
     *     ...
     *     break;
     *   }
     *   ...
     *   default: assert(false);
     * }
     *
     * Der default-Branch ist wichtig, damit du später keinen Bug produzierst, solltest du später
     * mal den State-enum erweitern und vergessen, dieses switch-Statement zu aktualisieren. Dann
     * wird der fehlende case hier als assert-error ausgegeben.
     */

/*
    switch (measurementState)
    {
    case State::Idle:{
        qDebug()<<"hi";
            //to Do: if abfrage-> ob das Programm bei Aktueller Temp bleiben soll, oder Energiesparmodus!
        }
    case State::ApproachStart:{
            if(std::abs(mSeqTc_->tempStart() - datapoint->ppmsdata()->pvTempLive()) < mSeqTc_->temperatureRate())
            {
                measurementState = State::ApproachEnd;
                instrumentmanager_->setTempSetpoint(mSeqTc_->tempEnd(), mSeqTc_->temperatureRate());
                fw_->append(datapoint);
            }
        }
    case State::ApproachEnd:{
           if(fw_!= nullptr){
                fw_->append(datapoint);
           }

           if(std::abs(mSeqTc_->tempEnd() - datapoint->ppmsdata()->pvTempLive()) < mSeqTc_->temperatureRate())
           {
                measurementState = State::Idle;
                measurementNumber_++;
           }
        }

    }
*/
    if(measurementState== State::ApproachStart &&
            std::abs(mSeqTc_->tempStart() - datapoint->ppmsdata()->pvTempLive()) < mSeqTc_->temperatureRate())
    {
        measurementState = State::ApproachEnd;
        instrumentmanager_->setTempSetpoint(mSeqTc_->tempEnd(), mSeqTc_->temperatureRate());
        fw_->append(datapoint);
    }

    if (fw_ != nullptr && measurementState==State::ApproachEnd)
    {
        fw_->append(datapoint);
    }

    if( measurementState==State::ApproachEnd &&
            std::abs(mSeqTc_->tempEnd() - datapoint->ppmsdata()->pvTempLive()) < mSeqTc_->temperatureRate())
    {
        measurementState = State::Idle;

        measurementNumber_++;
    }

}

InduManager::State InduManager::getMeasurementState() const
{
    return measurementState;
}


