#ifndef PPMSINSTRUMENT_H
#define PPMSINSTRUMENT_H
#include "Instruments_global.h"
#include <QObject>
#include <memory>
#include <QPair>
#include <string>
#include <locale>
#include <sstream>
#include <iomanip>
#include <iostream>
//Internal Classes
#include "gpib.h"
#include "../InduCore/datapoint.h"
#include "ppmsdatapoint.h"
#include "ppmsabstract.h"
class INSTRUMENTS_EXPORT PpmsInstrument : public PpmsAbstract
{
    Q_OBJECT
public:
    PpmsInstrument(std::shared_ptr<GPIB> gpib);

protected:
    void setTempSetpointCore(double setpoint, double rate) override;
    void setMagFieldCore(double magField, double magRate) override;
    void setAngleCore(double angle) override;
    QPair<double, double> tempSetpointCore() override;
    QPair<double, double> magFieldCore() override;
    double angleCore() override;
    double heliumCore() override;
    std::string ppmsStatus() override;
    PpmsDataPoint ppmsLogik() override;


private:
    void openDevice();
    std::string dtoStr (double number, int n);
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
    std::stringstream sstring_;
    std::shared_ptr<GPIB> gpib_;
    int address_;

};

#endif // PPMSCORE_H
