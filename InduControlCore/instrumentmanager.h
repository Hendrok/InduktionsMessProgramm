#ifndef INSTRUMENTMANAGER_H                          //Aufgabe: Daten von Messequence an PPMS-Core UND GBIB-Core weiter zu geben!
#define INSTRUMENTMANAGER_H
#include "InduControlCore_global.h"
#include <memory>
#include <QTimer>

//Internal Classes
#include "../InduCore/datapoint.h"
class QObject;
class PpmsSimulation;
class LockInSimulation;
class MeasSeqTc;

/* FIXME
 * - Forward declarations für QObject und MeasSeqTc sind unnötig
 * - In der Definition des Destructors fehlen Leerzeichen
 * - Methode SetInputVoltage startet mit einem Großbuchstaben
 * - Ein Kommentar zur Funktion der Klasse ist okay, aber nicht so
 *   wie aktuell oben rechts in der Ecke (auch Kommentare sollen
 *   nicht über die Mitte hinausgehen).
 *   Am Besten den Kommentar über mehrere Zeilen (so wie den hier)
 *   in Zeile 3 anfangen lassen (unterhalb des Include-Guards)
 */

class INDUCONTROLCORE_EXPORT InstrumentManager: public QObject
{
    Q_OBJECT
signals:
    void newData(std::shared_ptr<DataPoint> dataPoint);
public:
    InstrumentManager();
    ~InstrumentManager()=default;
    void setTempSetpoint(double setpoint, double rate);
    void SetInputVoltage(double InputVoltage);

private slots:
    void onPolling();

private:
    QTimer* timer_;
    std::shared_ptr<PpmsSimulation> ppmssimu_;
    std::shared_ptr<LockInSimulation> lockinsimu_ ;
};

#endif // INSTRUMENTMANAGER_H

