#ifndef INSTRUMENTMANAGER_H                          //Aufgabe: Daten von Messequence an PPMS-Core UND GBIB-Core weiter zu geben!
#define INSTRUMENTMANAGER_H
#include "InduControlCore_global.h"
#include <memory>
#include <QTimer>


//Eigene Klassen
#include "../InduCore/datapoint.h"


class QObject;
class PpmsSimulation;
class MeasurementSequence;

class INDUCONTROLCORE_EXPORT InstrumentManager: public QObject
{
    Q_OBJECT
signals:
    void newData(std::shared_ptr<DataPoint> dataPoint);
public:
    InstrumentManager();
    ~InstrumentManager();
    void setTempSetpoint(double setpoint, double rate);
private slots:
    void onPolling();
private:
    QTimer* timer_;
    PpmsSimulation* ppmssimu_;
    double tempSetpoint_;
    double tempRate_;
};

#endif // INSTRUMENTMANAGER_H

