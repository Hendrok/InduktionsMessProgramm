#ifndef MEASUREMENTSEQUENCE_H
#define MEASUREMENTSEQUENCE_H

#include "InduCore_global.h"
#include <QString>

class INDUCORE_EXPORT MeasurementSequence
{
public:
    MeasurementSequence();
    //algemein
    QString SupraName();
    void setSupraName(QString &supraName);
    //PPMS
    double TempStart();
    void setTempStart(double &tempStart);
    double TempEnd();
    void setTempEnd(double &tempEnd);
    double MagneticField();
    void setMagneticField(double &magneticField);
    double CoilAngle();
    void setCoilAngle(double &coilAngle);
    //GBIB
    double Frequency();
    void setFrequency(double &frequency);
    double VoltageAmplitude();
    void setVoltageAmplitude(double &voltageAmplitude);
    int HarmonicWave();
    void setHarmonicWave(int &harmonicWave);

private:
    //allgemein
    QString supraName_;
    //PPMS
    double tempStart_, tempEnd_; //von wo bis wo wird gemessen
    double temperatureRate_;
    double magneticField_;
    double coilAngle_;
    //GBIB
    double frequency_;
    double voltageAmplitude_;
    int harmonicWave_;

    };

#endif // MEASUREMENTSEQUENCE_H

inline QString MeasurementSequence::SupraName(){
    return supraName_;
}

inline void MeasurementSequence::setSupraName(QString &supraName){
    supraName_=supraName;
}

inline double MeasurementSequence::TempStart()
{
    return tempStart_;
}

inline void MeasurementSequence::setTempStart(double &tempStart)
{
    tempStart_=tempStart;
}

inline double MeasurementSequence::TempEnd()
{
    return tempEnd_;
}

inline void MeasurementSequence::setTempEnd(double &tempEnd)
{
    tempEnd_=tempEnd;
}

inline double MeasurementSequence::MagneticField()
{
    return magneticField_;
}

inline void MeasurementSequence::setMagneticField(double &magneticField)
{
    magneticField_=magneticField;
}

inline double MeasurementSequence::CoilAngle()
{
    return coilAngle_;
}

inline void MeasurementSequence::setCoilAngle(double &coilAngle)
{
    coilAngle_=coilAngle;
}

inline double MeasurementSequence::Frequency()
{
    return frequency_;
}

inline void MeasurementSequence::setFrequency(double &frequency)
{
    frequency_=frequency;
}

inline double MeasurementSequence::VoltageAmplitude()
{
    return voltageAmplitude_;
}

inline void MeasurementSequence::setVoltageAmplitude(double &voltageAmplitude)
{
    voltageAmplitude_=voltageAmplitude;
}

inline int MeasurementSequence::HarmonicWave()
{
    return harmonicWave_;
}

inline void MeasurementSequence::setHarmonicWave(int &harmonicWave)
{
    harmonicWave_=harmonicWave;
}



