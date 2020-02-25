#ifndef MEASSEQTC_H
#define MEASSEQTC_H

#endif // MEASSEQTC_H

#include "InduCore_global.h"
#include <QString>

#include "measurementsequence.h"

class INDUCORE_EXPORT MeasSeqTc : public MeasurementSequence
{
public:
    explicit MeasSeqTc();
    double tempStart() const;
    void setTempStart(double tempStart);
    double tempEnd() const;
    void setTempEnd(double tempEnd);
    double voltageAmplitude() const;
    void setVoltageAmplitude(double voltageAmplitude);

    double temperatureRate() const;
    void setTemperatureRate(double temperatureRate);

protected:
    double tempStart_;
    double tempEnd_;
    double voltageAmplitude_;
    double temperatureRate_;
};

inline MeasSeqTc::MeasSeqTc()
    : tempStart_(0)
    , tempEnd_(0)
    , voltageAmplitude_(1)
    , temperatureRate_(1)
{
}

inline double MeasSeqTc::tempStart() const
{
    return tempStart_;
}

inline void MeasSeqTc::setTempStart(double tempStart)
{
    tempStart_= tempStart;
}

inline double MeasSeqTc::tempEnd() const
{
    return tempEnd_;
}

inline void MeasSeqTc::setTempEnd(double tempEnd)
{
    tempEnd_= tempEnd;
}

inline double MeasSeqTc::voltageAmplitude() const
{
return voltageAmplitude_;
}

inline void MeasSeqTc::setVoltageAmplitude(double voltageAmplitude)
{
voltageAmplitude_ = voltageAmplitude;
}

inline double MeasSeqTc::temperatureRate() const
{
return temperatureRate_;
}

inline void MeasSeqTc::setTemperatureRate(double temperatureRate)
{
temperatureRate_ = temperatureRate;
}
