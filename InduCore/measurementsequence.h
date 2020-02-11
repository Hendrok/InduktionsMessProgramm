#ifndef MEASUREMENTSEQUENCE_H
#define MEASUREMENTSEQUENCE_H

#include "InduCore_global.h"
#include <QString>
//getter klein durch refactoring
class INDUCORE_EXPORT MeasurementSequence
{
public:
    MeasurementSequence();
    //algemein
    QString supraName() const;
    void setSupraName(const QString supraName);
    //PPMS
    double tempStart() const;
    void setTempStart(double tempStart);
    double tempEnd() const;
    void setTempEnd(double tempEnd);
    double magneticField() const;
    void setMagneticField (double magneticField);
    double coilAngle() const;
    void setCoilAngle(double coilAngle);
    //GBIB
    double frequency() const;
    void setFrequency(double frequency);
    double voltageAmplitude() const;
    void setVoltageAmplitude(double voltageAmplitude);
    int harmonicWave() const;
    void setHarmonicWave(int harmonicWave);

    double temperatureRate() const;
    void setTemperatureRate(double temperatureRate);

    QString fileName() const;
    void setFileName(const QString fileName);

private:
    //allgemein
    QString supraName_;
    QString fileName_;
    //PPMS
    double tempStart_;
    double tempEnd_; //von wo bis wo wird gemessen
    double temperatureRate_;
    double magneticField_;
    double coilAngle_;
    //Lockin
    double frequency_;
    double voltageAmplitude_;
    int harmonicWave_;

};

inline MeasurementSequence::MeasurementSequence()
    : supraName_("")
    , fileName_("")
    , tempStart_(0)
    , tempEnd_(0)
    , temperatureRate_(1)
    , magneticField_(0)
    , coilAngle_(0)
    , frequency_(33)
    , voltageAmplitude_(1)
    , harmonicWave_(1)
{}

inline QString MeasurementSequence::supraName() const
{
    return supraName_;
}

inline void MeasurementSequence::setSupraName(const QString supraName){
    supraName_= supraName;
}

inline double MeasurementSequence::tempStart() const
{
    return tempStart_;
}

inline void MeasurementSequence::setTempStart(double tempStart)
{
    tempStart_= tempStart;
}

inline double MeasurementSequence::tempEnd() const
{
    return tempEnd_;
}

inline void MeasurementSequence::setTempEnd(double tempEnd)
{
    tempEnd_= tempEnd;
}

inline double MeasurementSequence::magneticField() const
{
    return magneticField_;
}

inline void MeasurementSequence::setMagneticField(double magneticField)
{
    magneticField_= magneticField;
}

inline double MeasurementSequence::coilAngle() const
{
    return coilAngle_;
}

inline void MeasurementSequence::setCoilAngle(double coilAngle)
{
    coilAngle_= coilAngle;
}

inline double MeasurementSequence::frequency() const
{
    return frequency_;
}

inline void MeasurementSequence::setFrequency(double frequency)
{
    frequency_= frequency;
}

inline double MeasurementSequence::voltageAmplitude() const
{
    return voltageAmplitude_;
}

inline void MeasurementSequence::setVoltageAmplitude(double voltageAmplitude)
{
    voltageAmplitude_= voltageAmplitude;
}

inline int MeasurementSequence::harmonicWave() const
{
    return harmonicWave_;
}

inline void MeasurementSequence::setHarmonicWave(int harmonicWave)
{
    harmonicWave_= harmonicWave;
}

inline double MeasurementSequence::temperatureRate() const
{
    return temperatureRate_;
}

inline void MeasurementSequence::setTemperatureRate(double temperatureRate)
{
    temperatureRate_ = temperatureRate;
}

inline QString MeasurementSequence::fileName() const
{
    return fileName_;
}

inline void MeasurementSequence::setFileName(const QString fileName)
{
    fileName_ = fileName;
}



#endif // MEASUREMENTSEQUENCE_H
