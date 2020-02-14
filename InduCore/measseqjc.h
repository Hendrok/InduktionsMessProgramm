#ifndef MEASSEQJC_H
#define MEASSEQJC_H

#endif // MEASSEQJC_H

#include "InduCore_global.h"
#include "measurementsequence.h"


class INDUCORE_EXPORT MeasSeqJc : public MeasurementSequence
{
public:
    MeasSeqJc();
    double voltStart() const;
    void setVoltStart(double voltStart);

    double voltEnd() const;
    void setVoltEnd(double voltEnd);

    double voltRate() const;
    void setVoltRate(double voltRate);

    double temperature() const;
    void setTemperature(double temperature);

private:
    double voltStart_;
    double voltEnd_;
    double voltRate_;
    double temperature_;
};



MeasSeqJc::MeasSeqJc()
    : voltStart_(0.1)
    , voltEnd_ (1)
    , voltRate_ (0.01)
    , temperature_ (77)
{
}

inline double MeasSeqJc::voltStart() const
{
    return voltStart_;
}

inline void MeasSeqJc::setVoltStart(double voltStart)
{
    voltStart_ = voltStart;
}

inline double MeasSeqJc::voltEnd() const
{
return voltEnd_;
}

inline void MeasSeqJc::setVoltEnd(double voltEnd)
{
voltEnd_ = voltEnd;
}

inline double MeasSeqJc::voltRate() const
{
return voltRate_;
}

inline void MeasSeqJc::setVoltRate(double voltRate)
{
voltRate_ = voltRate;
}

inline double MeasSeqJc::temperature() const
{
return temperature_;
}

inline void MeasSeqJc::setTemperature(double temperature)
{
temperature_ = temperature;
}
