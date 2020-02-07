#ifndef INDUMANAGER_H
#define INDUMANAGER_H
#include "InduControlCore_global.h"
#include <memory>
#include <QObject>

//Eigene Klassen
#include "instrumentmanager.h"
#include "../InduCore/measurementsequence.h"
#include "../InduCore/datapoint.h"
#include "../InduCore/filewriter.h"
#include "instrumentmanager.h"
class INDUCONTROLCORE_EXPORT InduManager :public QObject
{
    Q_OBJECT

signals:
    void newData(std::shared_ptr<const DataPoint>);
public:
    InduManager();
    ~InduManager();

    void startMeasurement(std::shared_ptr<MeasurementSequence> &measurementSequence);
    //void startAppending(std::shared_ptr<MeasurementSequence> &measurementSequence, std::shared_ptr<DataPoint> &dataPoint);
private slots:
    void onNewData(std::shared_ptr<DataPoint> datapoint);
private:
    InstrumentManager *instrumentmanager_;
    std::unique_ptr <FileWriter> fw_;

};

#endif // INDUMANAGER_H
