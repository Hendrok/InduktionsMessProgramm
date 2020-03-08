#ifndef PPMSINSTRUMENT_H
#define PPMSINSTRUMENT_H
#include "Instruments_global.h"
#include <QObject>
#include <memory>
#include <QPair>
//Internal Classes
#include "../InduCore/datapoint.h"
#include "ppmsdatapoint.h"
#include "ppmsabstract.h"


class INSTRUMENTS_EXPORT PpmsInstrument : public PpmsAbstract
{
    Q_OBJECT
public:
    PpmsInstrument();

protected:
    void setTempSetpointCore(double setpoint, double rate) override;
    void setMagFieldCore(double magField, double magRate) override;
    void setAngleCore(double angle) override;
    QPair<double, double> tempSetpointCore() override;
    QPair<double, double> magFieldCore() override;
    double angleCore() override;
private:
    std::string dtoStr (double number);
    std::string itoStr (int number);
    double strtoD (std::string number);
    int strtoI (std::string number);
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

#endif // PPMSCORE_H
