#ifndef DATAPOINT_H
#define DATAPOINT_H

#include "InduCore_global.h"
#include <chrono>
#include <memory>
#include "../Instruments/ppmsdatapoint.h"
#include "../Instruments/lockindatapoint.h"

class INDUCORE_EXPORT DataPoint
{
public:
    DataPoint();

    std::chrono::system_clock::time_point time() const;
    void setTime(std::chrono::system_clock::time_point time);
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
    std::chrono::system_clock::time_point pvTime_;
    double pvTemp_;
    double pvField_;
    double pvAngle_;
    double pvVolt_;
    double pvPhase_;
    int pvPpmsStatus_;

    std::shared_ptr<const PpmsDataPoint> ppmsdata_;
    std::shared_ptr<const LockInDataPoint> lockindata_;


};
inline DataPoint::DataPoint()
    : pvTime_(std::chrono::system_clock::now())
    , pvTemp_(0)
    , pvField_(0)
    , pvAngle_(0)
    , pvVolt_(0)
    , pvPhase_(0)
    , pvPpmsStatus_(0)
    , ppmsdata_(std::make_shared<const PpmsDataPoint>())
    , lockindata_(std::make_shared<const LockInDataPoint>())


{
}


inline std::chrono::system_clock::time_point DataPoint::time() const
{
    return pvTime_;
}

inline void DataPoint::setTime(std::chrono::system_clock::time_point time)
{
    pvTime_=time;
}

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
    return pvPpmsStatus_;
}

inline void DataPoint::setpvStatusPPMS(int &pvStatusPPMS)
{
    pvPpmsStatus_=pvStatusPPMS;
}





#endif // DATAPOINT_H
