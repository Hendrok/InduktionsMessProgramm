#ifndef PPMSSIMULATION_H
#define PPMSSIMULATION_H
#include "Instruments_global.h"
#include <QObject>
#include <memory>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "ppmsdatapoint.h"

/* FIXME
 * - Diese beiden Forward-Declarations brauchst du nicht, da
 *   du das QObject includierst und MeasSeqTc hier nicht
 *   verwendest. Eine Klasse vorwärts zu deklarieren, von
 *   der man ableitet, würde eh nicht funktionieren, da man zum
 *   Ableiten die komplette Klassen-Definition benötigt
 */
class QObject;
class MeasSeqTc;


class INSTRUMENTS_EXPORT PpmsSimulation: public QObject
{
    Q_OBJECT
public:
    PpmsSimulation();
    void setTempSetpoint(double setpoint, double rate);
    void setPpmsVariables(double magField, double angle);

public slots:
    PpmsDataPoint generateVariables();
private:
    DataPoint datapoint_;
    double tempSetpoint_;
    double tempRate_;
    double fieldSetpoint_;
    double fieldRate_;
    double ppmsHelium_;
    double tempNow_;
    double magField_;
    double angle_;

};

#endif // PPMSSIMULATION_H
