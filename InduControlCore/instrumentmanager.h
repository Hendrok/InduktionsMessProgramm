#ifndef INSTRUMENTMANAGER_H                          //Aufgabe: Daten von Messequence an PPMS-Core UND GBIB-Core weiter zu geben!
#define INSTRUMENTMANAGER_H
#include "InduControlCore_global.h"
#include <memory>
#include "QObject"
#include <QTimer>

//Eigene Klassen
#include "../InduCore/datapoint.h"
#include "../InduCore/measurementsequence.h"

class INDUCONTROLCORE_EXPORT InstrumentManager: public QObject
{
    Q_OBJECT
signals:
    void newData(std::shared_ptr<DataPoint> datapoint);
public:
    InstrumentManager(std::shared_ptr<MeasurementSequence> measurementSequence);
    ~InstrumentManager();
    //void creatingRandomDataPoint(std::shared_ptr<MeasurementSequence> measurementSequence,std::shared_ptr<DataPoint> datapoint);
public slots:
    void createRandomDataPoints(/*std::shared_ptr<MeasurementSequence> measurementSequence*/);
private:
    QTimer* timer_;
    double starttemp_;
    double endtemp_;
    double currenttemp_;
};

#endif // INSTRUMENTMANAGER_H

