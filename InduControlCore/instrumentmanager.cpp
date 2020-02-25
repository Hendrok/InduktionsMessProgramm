#include "instrumentmanager.h"
#include <QDebug>
#include <QRandomGenerator>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "../Instruments/ppmssimulation.h"

/* FIXME
 * Wäre schön, wenn du hier in der Datei mal die ganzen übeflüssigen Leerzeilen
 * rausnehmen könntest.
 *
 * Grundregel mit Leerzeilen: Am Anfang und Ende einer Methode wird nichts leer gelassen,
 * also z.B:
 *
 * bool MyFunction()
 * {
 *    int someValue = 42;
 *    ...
 *    return true;
 * }
 *
 * Zwischendrin kann man einzelne Leerzeilen einsetzen, immer dann, wenn ein neuer
 * Gedanke anfängt. Absätze im Code haben etwa dieselbe Funktion wie Absätze in normalen
 * Text, immer wenn etwas "Neues" beginnt, sind einzelne Leerzeilen sinnvoll.
 *
 * Ausserdem gehören bei Template-Typen keine Leerzeichen hin:
 * std::make_shared<PpmsSimulation>()     Richtig
 * std::make_shared <PpmsSimulation>()     Falsch
 */

InstrumentManager::InstrumentManager()
    : timer_(new QTimer(this))
    , ppmssimu_(std::make_shared <PpmsSimulation>())
{


    connect(timer_, &QTimer::timeout, this, &InstrumentManager::onPolling);
    timer_->start(200);


}

void InstrumentManager::setTempSetpoint(double setpoint, double rate)
{
    ppmssimu_->setTempSetpoint(setpoint, rate);
}


void InstrumentManager::onPolling()
{

    auto dataPoint = ppmssimu_->generateVariablesTc();



    emit newData(dataPoint);


}
