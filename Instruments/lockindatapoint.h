#ifndef LOCKINDATAPOINT_H
#define LOCKINDATAPOINT_H


#include "Instruments_global.h"


class INSTRUMENTS_EXPORT LockInDataPoint
{
public:
    LockInDataPoint();

    double pvVoltSetPoint() const;
    void setPvVoltSetPoint(double pvVoltSetPoint);

    double pvVoltInputLive() const;
    void setPvVoltInputLive(double pvVoltInputLive);

    double pvVoltRate() const;
    void setPvVoltRate(double pvVoltRate);

    double pvPhase() const;
    void setPvPhase(double pvPhase);

    double pvVoltOutputLive() const;
    void setPvVoltOutputLive(double pvVoltOutputLive);

private:
    double pvVoltSetPoint_;     //höchstwahrscheinlich mit logik verbunden
    double pvVoltInputLive_;
    double pvVoltRate_;         //auch mit Logik verbunden
    double pvPhase_;
    double pvVoltOutputLive_;

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

inline double LockInDataPoint::pvVoltInputLive() const
{
return pvVoltInputLive_;
}

inline void LockInDataPoint::setPvVoltInputLive(double pvVoltLive)
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

inline double LockInDataPoint::pvVoltOutputLive() const
{
return pvVoltOutputLive_;
}

inline void LockInDataPoint::setPvVoltOutputLive(double pvVoltOutputLive)
{
pvVoltOutputLive_ = pvVoltOutputLive;
}



#endif // LOCKINDATAPOINT_H
