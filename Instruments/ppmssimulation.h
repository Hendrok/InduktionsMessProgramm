#ifndef PPMSSIMULATION_H
#define PPMSSIMULATION_H
#include "Instruments_global.h"
#include <QObject>
#include <memory>

//Internal Classes
#include "ppmsabstract.h"
#include "../InduCore/datapoint.h"
#include "ppmsdatapoint.h"

class INSTRUMENTS_EXPORT PpmsSimulation : public PpmsAbstract
{
    Q_OBJECT
public:
    PpmsSimulation();
    PpmsDataPoint generateVariables() override;
protected:
    void setTempSetpointCore(double setpoint, double rate) override;
    void setMagFieldCore(double magField, double magRate) override;
    void setAngleCore(double angle) override;
signals:
    void newTempSP(double setpoint, double rate);
    void newMagSP(double magField, double magRate);
    void newAngleSP(double angle);

private:
    DataPoint datapoint_;
    double tempSetpoint_;
    double tempRate_;
    double fieldSetpoint_;
    double fieldRate_;
    double ppmsHelium_;
    double tempNow_;
    double magFieldSP_;
    double magRate_;
    double magFieldNow_;
    double angle_;

};

#endif // PPMSSIMULATION_H
