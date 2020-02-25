#include "indumanager.h"
#include <QDebug>
#include <vector>

//Internal Classes
#include "instrumentmanager.h"
#include "../InduCore/measurementsequence.h"
#include "../InduCore/measseqtc.h"
#include "../InduCore/datapoint.h"
#include "../InduCore/filewriter.h"
#include "../Instruments/ppmsdatapoint.h"



InduManager::InduManager()
    : measurementNumber_(0)
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
  /* NOTE
   * der leere Deconstructor kann hier und in der Header-Datei weg, du machst
   * hier eh nix
   */
}



void InduManager::appendMeasurement(std::vector<std::shared_ptr<const MeasurementSequence> > mVecSeq)
{
    for (const auto mesSeq: mVecSeq)
    {
        mVecSeq_.push_back(mesSeq);
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

/* BUG
 * In den Zuständen ApproachStart und ApproachEnd überprüfst du, ob die Temperaturdifferenz zwischen Soll und Ist
 * kleiner ist als die Heiz- bzw. Kühlrate des PPMS. Warum?
 * Richtig wäre es, irgendeinen Differenz-Threshold zu definieren, z.b. 0.1 K oder so
 *
 * Nächster Bug im ApproachStart: Hier appendest du auch schon die Datenpunkte im FileWriter,
 * obwohl die Messung ja noch gar nicht begonnen hat
 */

/* NOTE
 * Bei Zustandsänderung könntest du ein Signal emitieren, dass als Argument den neuen Zustand enthält.
 * z.B.:
 *
 * void newState(State newState);
 *
 * Dann verbindest du im Mainwindow ein neuen Slot mit diesem Signal und kann in dem Slot dem Graphen
 * (und anderen Widgets, die später vllt. mal den Zustand brauchen) direkt weitergeben.
 * Damit könntest du dir auch den Getter getMeasurementState weiter unten sparen.
 */

/* NOTE
 * Grundsätzlich findet vieles deiner Prozesslogik hier im Switch-Statement statt,
 * mit Ausnahme des "Start Measurement"-Algorithmus.
 * Ich würde es sinnvoller finden, lieber noch einen weiteren State zu definieren, sowas wie
 * "setStartSetpoints" oder "StartMeasurement" (der Methodenname von oben) und dann den Algorithmus
 * auch im switch-Statement auszuführen. Dann ist alles, was für "Start/Stop/Warte/Speicher in Datei"
 * notwendig ist, hier an einer Stelle.
 */
void InduManager::onNewData(std::shared_ptr<DataPoint> datapoint)
{
    emit newData(datapoint);

    switch (measurementState)
    {
    case State::Idle:{
            //NOTE if abfrage-> ob das Programm bei Aktueller Temp bleiben soll, oder Energiesparmodus!
            break;
        }
    case State::ApproachStart:{
            if(std::abs(mSeqTc_->tempStart() - datapoint->ppmsdata()->pvTempLive()) < mSeqTc_->temperatureRate())
            {
                measurementState = State::ApproachEnd;
                instrumentmanager_->setTempSetpoint(mSeqTc_->tempEnd(), mSeqTc_->temperatureRate());
                fw_->append(datapoint);
            }
            break;
        }
    case State::ApproachEnd:{
           if(fw_!= nullptr){
                fw_->append(datapoint);
           }

           if(std::abs(mSeqTc_->tempEnd() - datapoint->ppmsdata()->pvTempLive()) < mSeqTc_->temperatureRate())
           {
               fw_->closeFile();
                measurementState = State::Idle;
                measurementNumber_++;
           }
            break;
        }

    default:assert(false);
    }
}

InduManager::State InduManager::getMeasurementState() const
{
    return measurementState;
}


