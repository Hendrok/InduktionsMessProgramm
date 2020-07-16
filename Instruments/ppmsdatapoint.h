#ifndef PPMSDATAPOINT_H
#define PPMSDATAPOINT_H

#include <string>

#include "Instruments_global.h"


class INSTRUMENTS_EXPORT PpmsDataPoint
{
public:
    PpmsDataPoint();


    double pvTempSetPoint() const;
    void setPvTempSetPoint(double pvTempSetPoint);

    double pvTempLive() const;
    void setPvTempLive(double pvTempLive);

    double pvTempRate() const;
    void setPvTempRate(double pvTempRate);

    double pvMagFieldLive() const;
    void setPvMagFieldLive(double pvMagFieldLive);

    double pvRotLive() const;
    void setPvRotLive(double pvRotLive);

    double pvChamberLevel() const;
    void setPvChamberLevel(double pvChamberLevel);

    std::string pvStatusPpms() const;
    void setPvStatusPpms(const std::string &pvStatusPpms);

    double pvMagSetPoint() const;
    void setPvMagSetPoint(double pvMagSetPoint);

    double pvRotSetPoint() const;
    void setPvRotSetPoint(double pvRotSetPoint);

    double pvSamplePressure() const;
    void setPvSamplePressure(double pvSamplePressure);

    double pvUserTemp() const;
    void setPvUserTemp(double pvUserTemp);

    std::uint32_t datamask() const;
    void setDatamask(const std::uint32_t &datamask);

private:
    //PpmsTemp
    double pvTempSetPoint_;
    double pvTempLive_;
    double pvUserTemp_;
    double pvTempRate_;

    //PpmsMag
    double pvMagFieldLive_;
    double pvMagSetPoint_;

    //PpmsRot
    double pvRotLive_;
    double pvRotSetPoint_;

    //PPmsHeliumChamber
    double pvChamberLevel_;
    double pvSamplePressure_;

    std::string pvStatusPpms_;
    std::uint32_t datamask_;
};
inline PpmsDataPoint::PpmsDataPoint()
    : pvTempSetPoint_(300)
    , pvTempLive_(300)
    , pvUserTemp_(300)
    , pvTempRate_(1)
    , pvMagFieldLive_(0)
    , pvMagSetPoint_(0)
    , pvRotLive_(0)
    , pvRotSetPoint_(0)
    , pvChamberLevel_(60)
    , pvSamplePressure_(0)
    , pvStatusPpms_("")
    , datamask_(0)
{
}

inline double PpmsDataPoint::pvTempSetPoint() const
{
    return pvTempSetPoint_;
}

inline void PpmsDataPoint::setPvTempSetPoint(double pvTempSetPoint)
{
    pvTempSetPoint_ = pvTempSetPoint;
}

inline double PpmsDataPoint::pvTempLive() const
{
    return pvTempLive_;
}

inline void PpmsDataPoint::setPvTempLive(double pvTempLive)
{
    pvTempLive_ = pvTempLive;
}

inline double PpmsDataPoint::pvTempRate() const
{
    return pvTempRate_;
}

inline void PpmsDataPoint::setPvTempRate(double pvTempRate)
{
    pvTempRate_ = pvTempRate;
}

inline double PpmsDataPoint::pvMagFieldLive() const
{
    return pvMagFieldLive_;
}

inline void PpmsDataPoint::setPvMagFieldLive(double pvMagFieldLive)
{
    pvMagFieldLive_ = pvMagFieldLive;
}

inline double PpmsDataPoint::pvRotLive() const
{
    return pvRotLive_;
}

inline void PpmsDataPoint::setPvRotLive(double pvRotLive)
{
    pvRotLive_ = pvRotLive;
}

inline double PpmsDataPoint::pvChamberLevel() const
{
    return pvChamberLevel_;
}

inline void PpmsDataPoint::setPvChamberLevel(double pvChamberLevel)
{
    pvChamberLevel_ = pvChamberLevel;
}

inline std::string PpmsDataPoint::pvStatusPpms() const
{
return pvStatusPpms_;
}

inline void PpmsDataPoint::setPvStatusPpms(const std::string &pvStatusPpms)
{
pvStatusPpms_ = pvStatusPpms;
}

inline double PpmsDataPoint::pvMagSetPoint() const
{
return pvMagSetPoint_;
}

inline void PpmsDataPoint::setPvMagSetPoint(double pvMagSetPoint)
{
pvMagSetPoint_ = pvMagSetPoint;
}

inline double PpmsDataPoint::pvRotSetPoint() const
{
return pvRotSetPoint_;
}

inline void PpmsDataPoint::setPvRotSetPoint(double pvRotSetPoint)
{
pvRotSetPoint_ = pvRotSetPoint;
}

inline double PpmsDataPoint::pvSamplePressure() const
{
return pvSamplePressure_;
}

inline void PpmsDataPoint::setPvSamplePressure(double pvSamplePressure)
{
pvSamplePressure_ = pvSamplePressure;
}

inline double PpmsDataPoint::pvUserTemp() const
{
return pvUserTemp_;
}

inline void PpmsDataPoint::setPvUserTemp(double pvUserTemp)
{
pvUserTemp_ = pvUserTemp;
}

inline std::uint32_t PpmsDataPoint::datamask() const
{
return datamask_;
}

inline void PpmsDataPoint::setDatamask(const std::uint32_t &datamask)
{
datamask_ = datamask;
}





#endif // PPMSDATAPOINT_H
