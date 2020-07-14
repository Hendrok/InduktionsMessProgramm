#include "filewriter.h"
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QDir>
#include "measurementsequence.h"
#include "measseqtc.h"
#include "measseqjc.h"
#include "datapoint.h"
#include "filewriter.h"


FileWriter::FileWriter(QObject *parent)
    :QObject(parent)
{
}

QString FileWriter::writeHeader(std::shared_ptr<const MeasurementSequence> measurementSequence){
        auto seqTc = std::dynamic_pointer_cast<const MeasSeqTc> (measurementSequence);
        auto seqJc = std::dynamic_pointer_cast<const MeasSeqJc> (measurementSequence);

        if(seqTc !=nullptr)
        {
            QString header_;
            header_.append("Sample Name: ");
            header_.append(measurementSequence->supraName());
            header_.append("\nVoltage: ");
            header_.append(QString::number(seqTc->voltageAmplitude()));
            header_.append(" V \nFrequency: ");
            header_.append(QString::number(measurementSequence->frequency()));
            header_.append(" hz \nMagnetic Field: ");
            header_.append(QString::number(measurementSequence->magneticField()));
            header_.append(" mT \nStarting Temperature: ");
            header_.append(QString::number(seqTc->tempStart()));
            header_.append(" K \nEnding Temperature: ");
            header_.append(QString::number(seqTc->tempEnd()));
            header_.append(" K \nTemperature Rate: ");
            header_.append(QString::number(seqTc->temperatureRate()));
            header_.append(" K/min \nHarmonic Wave: ");
            header_.append(QString::number(measurementSequence->harmonicWave()));
            header_.append("\nCoilAngle: ");
            header_.append(QString::number(measurementSequence->coilAngle()));
            header_.append(" degrees \n");
            header_.append("Temperature UserTemp Voltage Phase \n");
            return header_;
        }

        else if (seqJc !=nullptr)
        {
            QString header_;
            header_.append("Material: ");
            header_.append(measurementSequence->supraName());
            header_.append("\n Temperature: ");
            header_.append(QString::number(seqJc->temperature()));
            header_.append(" T \n Frequency: ");
            header_.append(QString::number(measurementSequence->frequency()));
            header_.append(" hz \n Magnetic Field: ");
            header_.append(QString::number(measurementSequence->magneticField()));
            header_.append(" mT \n Starting Voltage: ");
            header_.append(QString::number(seqJc->voltStart()));
            header_.append(" V \n Ending Voltage: ");
            header_.append(QString::number(seqJc->voltEnd()));
            header_.append(" V \n Voltage Rate: ");
            header_.append(QString::number(seqJc->voltRate()));
            header_.append(" V/min \n Harmonic Wave: ");
            header_.append(QString::number(measurementSequence->harmonicWave()));
            header_.append("\n CoilAngle: ");
            header_.append(QString::number(measurementSequence->coilAngle()));
            header_.append(" degrees \n");
            header_.append("Input_Voltage Output_Voltage Phase \n");
            return header_;
        }
        else{return "unable to write header";}
}
QString FileWriter::createFileName(std::shared_ptr<const MeasurementSequence> measurementSequence){
        auto seqTc = std::dynamic_pointer_cast<const MeasSeqTc> ( measurementSequence);
        auto seqJc = std::dynamic_pointer_cast<const MeasSeqJc> (measurementSequence);
        if(seqTc !=nullptr)
        {
            QString filename_= "Tc_";
            filename_.append(measurementSequence->fileName());
            return filename_;
        }
        else if(seqJc !=nullptr)
        {
            QString filename_= "Jc_";
            filename_.append(measurementSequence->fileName());
            return filename_;
        }
        else {return "Neither Tc or Jc";}
}
void FileWriter::append(std::shared_ptr<DataPoint> datapoint){
        if(!file_->isOpen())
        {
            return;
        }
        if(measurementState_ == InduManager::State::ApproachEndTc)
        {
        file_->write(QString::number(datapoint->ppmsdata()->pvTempLive()).toUtf8() +
                     " " + QString::number(datapoint->ppmsdata()->pvUserTemp()).toUtf8() +
                     " " + QString::number(datapoint->lockindata()->pvVoltOutputLive()).toUtf8() +
                     " " + QString::number(datapoint->lockindata()->pvPhase()).toUtf8() + "\n");
        }
        else if(measurementState_ == InduManager::State::ApproachEndJc)
        {
            file_->write(QString::number(datapoint->lockindata()->pvVoltInputLive()).toUtf8() +
                         " " + QString::number(datapoint->lockindata()->pvVoltOutputLive()).toUtf8() +
                         " " + QString::number(datapoint->lockindata()->pvPhase()).toUtf8() +
                         " " + QString::number(datapoint->ppmsdata()->pvUserTemp()).toUtf8() + "\n");

        }
}

QString FileWriter::openFile(std::shared_ptr<const MeasurementSequence> measurementSequence){
        QString path("Messergebnisse/");
        QDir dir;  // ich erstelle QString mit dem Ordner, danach die direction
        if (!dir.exists(path)){ // Wenn nötig wird der Ordner erstellt
            dir.mkpath(path);
        }

        QString filepath = createFileName(measurementSequence);
        // der Filename und path wird gesezt, außerdem wird der name mit (i) verändert, wenn es die Txt datei schon  gibt
        QFile file(path + filepath + ".txt");
        for(int i=1; file.exists();i++)
        {
            if (file.exists()){
                file.setFileName(path + filepath + "_("+QString::number(i) + ")" ".txt");
            }
        }

        file.open(QIODevice::WriteOnly);
        file_ = std::make_shared<QFile>(file.fileName());

        file_->open(QIODevice::WriteOnly | QIODevice::Text);

        if(!file_->isOpen())
        {
            return QString();
        }
        if(file_->isWritable()){
            file_->write(writeHeader(measurementSequence).toUtf8());
        }
        return file_->fileName();
}

void FileWriter::closeFile()
{
    file_->close();
}

void FileWriter::MeasurementState(InduManager::State newState)
{
    measurementState_ = newState;
}
