#ifndef INDUMANAGER_H
#define INDUMANAGER_H
#include "InduControlCore_global.h"
#include <memory>
#include <QObject>



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
public:
    explicit InduManager();
    ~InduManager();
    enum class State { Idle, ApproachStart, ApproachEnd};
    void startMeasurement(std::shared_ptr<const MeasurementSequence> measurementSequence);

    State getMeasurementState() const;

private slots:
    void onNewData(std::shared_ptr<DataPoint> datapoint);

private:
    std::unique_ptr <InstrumentManager> instrumentmanager_;
    std::unique_ptr <FileWriter> fw_;    
    std::shared_ptr <MeasSeqTc> mSeqTc_;  // muss ich noch auf measurementsequence wechsekln
    State measurementState;
};

#endif // INDUMANAGER_H
