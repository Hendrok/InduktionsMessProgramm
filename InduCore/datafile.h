#ifndef DATAFILE_H
#define DATAFILE_H

#include <QVector>
#include <memory>
#include "InduCore_global.h" //hier ist das export macro, sonst kann ich INDUCORE_EXPORT nicht benutzen beim deklarieren der Klasse
#include "measurementsequence.h"
#include "MeasSeqTc.h"
class INDUCORE_EXPORT Datafile
{
public:
   QVector<double> getTemperature();
   void setTemperatur(QVector<double> &temperature);
   QVector<double> getVoltage();
   void setVoltage(QVector<double> &voltage);
   QString getInputText();
   void setInputText(QString &filename);
   QString getFileName();
   void setFileName(QString &filename);
private:
    QVector<double> temperature_;
    QVector<double> voltage_;
    QVector<double> phaseShift_;
    QString inputText_;
    QString filename_;

    //attribute
    std::shared_ptr<MeasSeqTc>  MeasurementPointer;

};

// Getter and Setter für Temperature
inline QVector<double> Datafile::getTemperature()
{
    return temperature_;
}

inline void Datafile::setTemperatur(QVector<double> &temperature){
    temperature_= temperature;
}

// Getter und Setter für Voltage

inline QVector<double> Datafile::getVoltage(){
    return voltage_;
}

inline void Datafile::setVoltage(QVector<double> &voltage){
    voltage_= voltage;
}

// Getter und Setter für Filename

inline QString Datafile::getInputText(){
    return inputText_;
}
inline void Datafile::setInputText(QString &inputText){
    inputText_= inputText;
}

inline QString Datafile::getFileName(){
    return filename_;
}
inline void Datafile::setFileName(QString &filename){
    filename_= filename;
}

//parameter




#endif // DATAFILE_H

