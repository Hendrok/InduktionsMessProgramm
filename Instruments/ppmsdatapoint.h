#ifndef PPMSDATAPOINT_H
#define PPMSDATAPOINT_H


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

    double pvMagSetPoint() const;
    void setPvMagSetPoint(double pvMagSetPoint);

    double pvMagFieldLive() const;
    void setPvMagFieldLive(double pvMagFieldLive);

    double pvRotSetPoint() const;
    void setPvRotSetPoint(double pvRotSetPoint);

    double pvRotLive() const;
    void setPvRotLive(double pvRotLive);

    double pvChamberLevel() const;
    void setPvChamberLevel(double pvChamberLevel);

    int pvStatusPpms() const;
    void setPvStatusPpms(int pvStatusPpms);

private:

    //PpmsTemp
    double pvTempSetPoint_;
    double pvTempLive_;
    double pvTempRate_;

    //PpmsMag
    double pvMagSetPoint_;
    double pvMagFieldLive_;

    //PpmsRot
    double pvRotSetPoint_;
    double pvRotLive_;

    //PPmsHeliumChamber
    double pvChamberLevel_;

    int pvStatusPpms_;
};

inline PpmsDataPoint::PpmsDataPoint()
    : pvTempSetPoint_(300)
    , pvTempLive_(300)
    , pvTempRate_(1)
    , pvMagSetPoint_(0)
    , pvMagFieldLive_(0)
    , pvRotSetPoint_(0)
    , pvRotLive_(0)
    , pvChamberLevel_(60)
    , pvStatusPpms_(0)
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

inline double PpmsDataPoint::pvMagSetPoint() const
{
return pvMagSetPoint_;
}

inline void PpmsDataPoint::setPvMagSetPoint(double pvMagSetPoint)
{
pvMagSetPoint_ = pvMagSetPoint;
}

inline double PpmsDataPoint::pvMagFieldLive() const
{
return pvMagFieldLive_;
}

inline void PpmsDataPoint::setPvMagFieldLive(double pvMagFieldLive)
{
pvMagFieldLive_ = pvMagFieldLive;
}

inline double PpmsDataPoint::pvRotSetPoint() const
{
return pvRotSetPoint_;
}

inline void PpmsDataPoint::setPvRotSetPoint(double pvRotSetPoint)
{
pvRotSetPoint_ = pvRotSetPoint;
}

double PpmsDataPoint::pvRotLive() const
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

int PpmsDataPoint::pvStatusPpms() const
{
return pvStatusPpms_;
}

void PpmsDataPoint::setPvStatusPpms(int pvStatusPpms)
{
pvStatusPpms_ = pvStatusPpms;
}


#endif // PPMSDATAPOINT_H
