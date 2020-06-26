#include "lockinsimulation.h"
#include <QRandomGenerator>
#include <memory>
#include <QDebug>
#include <QTime>
//Internal Classes
#include "../InduCore/datapoint.h"
#include "../InduControlCore/instrumentmanager.h"
#include "../Instruments/ppmsdatapoint.h"
#include "../Instruments/lockindatapoint.h"
#include <windows.h> // for Sleep
/* FIXME
 * Im Moment setzt du die Setpoints als interne Attribute, was soweit
 * korrekt ist, das habe ich auch so gemacht. Allerdings emittierst du
 * die Signale immer in der Polling-Methode, was nicht ganz der Simulation
 * der Hardware entspricht. Normalweise sollte das Signal emittiert werden,
 * nachdem der Setpoint gesetzt wurde.
 *
 * Logik also etwa so:
 *    1.) Die Klasse bekommt einen neuen Setpoint als Request, also z.b.
 *        setInputVoltage(3.4)
 *    2.) Die Klasse muss überprüfen, ob der Setpoint sinnvoll ist
 *        (sowas nennt man "Sanity-Check")
 *    3.) Die Klasse muss den Setpoint (notfalls einen getrimmten Setpoint,
 *        der innerhalb der zulässigen Grenzen liegt) an den GPIB weitergeben
 *    4.) Die Klasse muss nach dem gesetzen Setpoint am Gerät nachfragen, ob
 *        der Setpoint auch tatsächlich gesetzt wurde
 *        Gründe, warum Setpoints nicht gesetzt werden könnten:
 *          - Gerät im Fehlermodus
 *          - Noise auf dem Feldbus (Übertragungsfehler)
 *          - etc
 *    5.) Nachdem die Klasse den aktuellen Setpoint vom Gerät ausgelesen hat,
 *        wird dieser Setpoint als Signal zurück emittiert.
 *
 * Da du in der Simulationsklasse nicht mit echter Hardware zu tun hast, kannst du
 * dir hier all diese Schritte sparen. Ich würde einfach den aktuellen Setpoint, den
 * du ins Attribut kopiert hast, zurück an den Absender schicken. So also:
 *
 * void LockInSimulation::setInputVoltage(double InputVoltage)
 * {
 *    inputVoltage_ = InputVoltage;
 *    emit newInputVoltageSetpoint(inputVoltage_);
 * }
 *
 * Die emit-Signale in der Polling-Methode würde ich entfernen (außer dem emit
 * datapoint natürlich)
 */

LockInSimulation::LockInSimulation()
    : datapoint_(DataPoint())
    , inputVoltage_ (0.1)
    , voltnow_(0.1)
    , freq_(0)
    , sensivity_(0)
    , harmonicW_(1)
{  
}

void LockInSimulation::setInputVoltageCore(double inputVoltage)
{
    inputVoltage_ = inputVoltage;
}

void LockInSimulation::setFreqCore(double freq)
{
    freq_ = freq;
}

void LockInSimulation::setSensivityCore(int sensivity)
{
    sensivity_ = sensivity;
}

void LockInSimulation::setHarmonicCore(int harmonicW)
{
    harmonicW_ = harmonicW;
}

void LockInSimulation::delay()
{
  //  _sleep(1000);
}

double LockInSimulation::inputVoltageCore()
{
    return inputVoltage_;
}

double LockInSimulation::freqCore()
{
    return freq_;
}

int LockInSimulation::sensitivityCore()
{
    return sensivity_;
}

int LockInSimulation::harmonicCore()
{
    return harmonicW_;
}

LockInDataPoint LockInSimulation::lockInLogik()
{
    LockInDataPoint lockingDpoint;

    auto dataPoint =std::make_shared<DataPoint> ();
    double test =QRandomGenerator::global()->bounded(1.0);
    delay();
    lockingDpoint.setPvVoltOutputLive(test);
    lockingDpoint.setPvPhase(test+90);
    lockingDpoint.setPvVoltInputLive(inputVoltage_);

    return lockingDpoint;

}
