#ifndef MEASUREMENTSEQUENCE_H
#define MEASUREMENTSEQUENCE_H

#include "InduCore_global.h"
#include <QString>
//getter klein durch refactoring
class INDUCORE_EXPORT MeasurementSequence
{
public:
    MeasurementSequence();
    virtual ~MeasurementSequence()=0;
    //algemein
    QString supraName() const;
    void setSupraName(const QString supraName);
    //PPMS

    double magneticField() const;
    void setMagneticField (double magneticField);
    double coilAngle() const;
    void setCoilAngle(double coilAngle);
    //GBIB
    double frequency() const;
    void setFrequency(double frequency);
    int harmonicWave() const;
    void setHarmonicWave(int harmonicWave);
    QString fileName() const;
    void setFileName(const QString fileName);

    protected:
    //allgemein
    QString supraName_;
    QString fileName_;
    //PPMS
    double magneticField_;
    double coilAngle_;
    //Lockin
    double frequency_;

    int harmonicWave_;

};

inline MeasurementSequence::MeasurementSequence()
    : supraName_("")
    , fileName_("")
    , magneticField_(0)
    , coilAngle_(0)
    , frequency_(33)

    , harmonicWave_(1)
{}

inline MeasurementSequence::~MeasurementSequence()
{

}

inline QString MeasurementSequence::supraName() const
{
    return supraName_;
}

inline void MeasurementSequence::setSupraName(const QString supraName){
    supraName_= supraName;
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

inline int MeasurementSequence::harmonicWave() const
{
    return harmonicWave_;
}

inline void MeasurementSequence::setHarmonicWave(int harmonicWave)
{
    harmonicWave_= harmonicWave;
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
