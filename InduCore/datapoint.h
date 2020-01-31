#ifndef DATAPOINT_H
#define DATAPOINT_H
//gibt den in der aktuellen schleife aus     pvtemp_   was fehlt status int; jedes bit hat speziellen status. das auch hinzufügen rest bei marco gucken, wichtig das mit pv zu bezeichnen!
#include "InduCore_global.h"
class INDUCORE_EXPORT DataPoint
{
public:
    DataPoint();
    double pvTemp() const;
    void setpvTemp(double pvTemp);
    double pvField() const;
    void setpvField(double pvField);
    double pvAngle() const;
    void setpvAngle(double pvAngle);
    double pvVolt() const;
    void setpvVolt(double pvVolt);
    double pvPhase() const;
    void setpvPhase(double pvPhase);
    int pvStatusPPMS() const;
    void setpvStatusPPMS(int &pvStatusPPMS);

private:
    double pvTemp_;
    double pvField_;
    double pvAngle_;
    double pvVolt_;
    double pvPhase_;
    int pvStatusPPMS_;
};

inline double DataPoint::pvTemp() const
{
    return pvTemp_;
}

inline void DataPoint::setpvTemp(double temp)
{
    pvTemp_ = temp;
}

inline double DataPoint::pvField() const
{
    return pvField_;
}

inline void DataPoint::setpvField(double field)
{
    pvField_ = field;
}

inline double DataPoint::pvAngle() const
{
    return pvAngle_;
}

inline void DataPoint::setpvAngle(double angle)
{
    pvAngle_ = angle;
}

inline double DataPoint::pvVolt() const
{
    return pvVolt_;
}

inline void DataPoint::setpvVolt(double volt)
{
    pvVolt_ = volt;
}

inline double DataPoint::pvPhase() const
{
    return pvPhase_;
}

inline void DataPoint::setpvPhase(double phase)
{
    pvPhase_ = phase;
}

inline int DataPoint::pvStatusPPMS() const
{
    return pvStatusPPMS_;
}

void DataPoint::setpvStatusPPMS(int &pvStatusPPMS)
{
    pvStatusPPMS_=pvStatusPPMS;
}




#endif // DATAPOINT_H
