#ifndef INDUMANAGER_H
#define INDUMANAGER_H
#include "InduControlCore_global.h"
#include <memory>
#include <QObject>


//forward
class PpmsSimulation;
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
    InduManager();
    ~InduManager();

    void startMeasurement(std::shared_ptr<const MeasurementSequence> &measurementSequence);

private slots:
    void onNewData(std::shared_ptr<DataPoint> datapoint);

private:
    InstrumentManager *instrumentmanager_;
    std::unique_ptr <FileWriter> fw_;


};

#endif // INDUMANAGER_H
