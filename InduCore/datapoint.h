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

    std::shared_ptr<const PpmsDataPoint> ppmsdata() const;
    void setPpmsdata(const std::shared_ptr<const PpmsDataPoint> &ppmsdata);

    std::shared_ptr<const LockInDataPoint> lockindata() const;
    void setLockindata(const std::shared_ptr<const LockInDataPoint> &lockindata);

private:


    std::shared_ptr<const PpmsDataPoint> ppmsdata_;
    std::shared_ptr<const LockInDataPoint> lockindata_;


};
inline DataPoint::DataPoint()
    : ppmsdata_(std::make_shared<const PpmsDataPoint>())
    , lockindata_(std::make_shared<const LockInDataPoint>())
{
}



inline std::shared_ptr<const PpmsDataPoint> DataPoint::ppmsdata() const
{
return ppmsdata_;
}

inline void DataPoint::setPpmsdata(const std::shared_ptr<const PpmsDataPoint> &ppmsdata)
{
ppmsdata_ = ppmsdata;
}

inline std::shared_ptr<const LockInDataPoint> DataPoint::lockindata() const
{
return lockindata_;
}

inline void DataPoint::setLockindata(const std::shared_ptr<const LockInDataPoint> &lockindata)
{
lockindata_ = lockindata;
}




#endif // DATAPOINT_H
