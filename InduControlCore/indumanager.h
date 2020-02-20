#ifndef INDUMANAGER_H
#define INDUMANAGER_H
#include "InduControlCore_global.h"
#include <memory>
#include <QObject>
#include <vector>


//forward
class PpmsSimulation;
class MeasSeqTc;
class MeasurementSequence;
class DataPoint;
class FileWriter;
class InstrumentManager;


class INDUCONTROLCORE_EXPORT InduManager :public QObject
{
    Q_OBJECT

signals:
    void newData(std::shared_ptr<const DataPoint>);
    void startNewMeasurement(std::shared_ptr<const MeasurementSequence>);
public:
    explicit InduManager();
    ~InduManager();
    enum class State { Idle, ApproachStart, ApproachEnd};
    void appendMeasurement(std::vector <std::shared_ptr<const MeasurementSequence>> mVecSeq);
    void checkStartMeasurement();
    void startMeasurement(std::shared_ptr<const MeasurementSequence> measurementSequence);

    State getMeasurementState() const;

private slots:
    void onNewData(std::shared_ptr<DataPoint> datapoint);

private:   
    int measurementNumber_;
    std::vector<std::shared_ptr<const MeasurementSequence> > mVecSeq_;
    std::unique_ptr <InstrumentManager> instrumentmanager_;
    std::unique_ptr <FileWriter> fw_;        
    std::shared_ptr <MeasSeqTc> mSeqTc_;  // muss ich noch auf measurementsequence wechseln
    State measurementState;
};

#endif // INDUMANAGER_H
