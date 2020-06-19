#ifndef PPMSSIMULATION_H
#define PPMSSIMULATION_H
#include "Instruments_global.h"
#include <QObject>
#include <memory>
#include <QPair>

//Internal Classes
#include "ppmsabstract.h"
#include "../InduCore/datapoint.h"
#include "ppmsdatapoint.h"


class INSTRUMENTS_EXPORT PpmsSimulation : public PpmsAbstract
{
    Q_OBJECT
public:
    PpmsSimulation();

protected:
    void setTempSetpointCore(double setpoint, double rate) override;
    void setMagFieldCore(double magField, double magRate) override;
    void setAngleCore(double angle) override;
    QPair<double,double> tempSetpointCore() override;
    QPair<double, double> magFieldCore() override;
    double angleCore() override;
    double heliumCore() override;
    std::string ppmsStatus() override;
    PpmsDataPoint ppmsLogik() override;


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
