#ifndef LOCKINDATAPOINT_H
#define LOCKINDATAPOINT_H


#include "Instruments_global.h"


class INSTRUMENTS_EXPORT LockInDataPoint
{
public:
    LockInDataPoint();

    double pvVoltSetPoint() const;
    void setPvVoltSetPoint(double pvVoltSetPoint);

    double pvVoltLive() const;
    void setPvVoltLive(double pvVoltLive);

    double pvVoltRate() const;
    void setPvVoltRate(double pvVoltRate);

    double pvPhase() const;
    void setPvPhase(double pvPhase);

private:
    double pvVoltSetPoint_;     //höchstwahrscheinlich mit logik verbunden
    double pvVoltInputLive_;
    double pvVoltRate_;         //auch mit Logik verbunden

    double pvPhase_;
};
inline LockInDataPoint::LockInDataPoint()
    : pvVoltSetPoint_(0)
    , pvVoltInputLive_(0)
    , pvVoltRate_(0)
    , pvPhase_(0)
{
}

inline double LockInDataPoint::pvVoltSetPoint() const
{
return pvVoltSetPoint_;
}

inline void LockInDataPoint::setPvVoltSetPoint(double pvVoltSetPoint)
{
pvVoltSetPoint_ = pvVoltSetPoint;
}

inline double LockInDataPoint::pvVoltLive() const
{
return pvVoltInputLive_;
}

inline void LockInDataPoint::setPvVoltLive(double pvVoltLive)
{
pvVoltInputLive_ = pvVoltLive;
}

inline double LockInDataPoint::pvVoltRate() const
{
return pvVoltRate_;
}

inline void LockInDataPoint::setPvVoltRate(double pvVoltRate)
{
pvVoltRate_ = pvVoltRate;
}

inline double LockInDataPoint::pvPhase() const
{
return pvPhase_;
}

inline void LockInDataPoint::setPvPhase(double pvPhase)
{
pvPhase_ = pvPhase;
}


#endif // LOCKINDATAPOINT_H
