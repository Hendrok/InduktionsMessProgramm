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
    PpmsInstrument(std::shared_ptr<GPIB> gpib, int address);
    void openDevice() override;
    void newRotatorstate(bool rotator) override;
    bool isOpen() const override;

protected:
    void setTempSetpointCore(double setpoint, double rate) override;
    void setMagFieldCore(double magField, double magRate) override;
    void setAngleCore(double angle) override;
    QPair<double, double> tempSetpointCore() override;
    QPair<double, double> magFieldCore() override;
    double angleCore() override;
    double heliumCore() override;
    PpmsDataPoint ppmsLogik() override;

private:
    std::string dtoStr (double number, int n);
    std::stringstream sstring_;
    std::shared_ptr<GPIB> gpib_;
    int address_;
    bool rotState_;
    std::int32_t dataMask_;

};

#endif // PPMSCORE_H
