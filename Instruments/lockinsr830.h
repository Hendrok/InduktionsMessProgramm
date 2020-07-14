#ifndef LOCKINSR830_H
#define LOCKINSR830_H

#include "Instruments_global.h"
#include <QObject>
#include <memory>
#include <string>
#include <locale>
#include <sstream>
#include <iomanip>
#include <iostream>

//Internal Classes
#include "gpib.h"
#include "../InduCore/datapoint.h"
#include "lockindatapoint.h"
#include "lockinabstract.h"

class INSTRUMENTS_EXPORT LockInSr830 : public LockInAbstract
{
    Q_OBJECT
public:
    LockInSr830(std::shared_ptr<GPIB> gpib);
    void openDevice() override;
protected:
    void setInputVoltageCore(double inputVoltage) override;
    void setFreqCore(double freq) override;
    void setHarmonicCore(int harmonicW) override;
    void setSensivityCore(int sensivity) override;
    double inputVoltageCore() override;
    double freqCore() override;
    int harmonicCore() override;
    int sensitivityCore() override;
    LockInDataPoint lockInLogik() override;
private:
    std::string dtoStr (double number, int dec);
    std::string itoStr (int number);
    double strtoD (std::string number);
    int strtoI (std::string number);
    DataPoint datapoint_;
    double inputVoltage_;
    double voltnow_;
    double freq_;
    double sensivity_;
    double harmonicW_;
    double phase_;
    std::stringstream sstring_ ;
    std::shared_ptr<GPIB> gpib_;
    int address_;

};

#endif
