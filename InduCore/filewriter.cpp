#include "filewriter.h"

#include <QString>
#include <QTextStream>
#include <QDir>
FileWriter::FileWriter()

{

}

QString FileWriter::writeHeader(std::shared_ptr<MeasurementSequence> measurementSequence){
        //wasobenintextdateisteht später
      QString header_;
      header_.append("Material: ");
      header_.append(measurementSequence->supraName());
      header_.append("\n Voltage: ");
      header_.append(QString::number(measurementSequence->voltageAmplitude()));
      header_.append(" V \n Frequency: ");
      header_.append(QString::number(measurementSequence->frequency()));
      header_.append(" hz \n Magnetic Field: ");
      header_.append(QString::number(measurementSequence->magneticField()));
      header_.append(" mT \n Starting Temperature: ");
      header_.append(QString::number(measurementSequence->tempStart()));
      header_.append(" K \n Ending Temperature: ");
      header_.append(QString::number(measurementSequence->tempEnd()));
      header_.append(" K \n Temperature Rate: ");
      header_.append(QString::number(measurementSequence->temperatureRate()));
      header_.append(" K/min \n Harmonic Wave: ");
      header_.append(QString::number(measurementSequence->harmonicWave()));
      header_.append("\n CoilAngle: ");
      header_.append(QString::number(measurementSequence->coilAngle()));
      if(measurementSequence->coilAngle()==1) {header_.append(" degree \n"); }
      else{
      header_.append(" degrees \n");
      }



/*if (header_==""){
    return false;
}
else{
    return true;
}*/
      return header_;
}
QString FileWriter::createFileName(std::shared_ptr<MeasurementSequence> measurementSequence){
    QString filename_;
    filename_.append(measurementSequence->supraName());
    filename_.append("_");
    filename_.append(QString::number(measurementSequence->voltageAmplitude()));
    filename_.append("V_");
    filename_.append(QString::number(measurementSequence->frequency()));
    filename_.append("hz_");
    filename_.append(QString::number(measurementSequence->magneticField()));
    filename_.append("mT_");
    filename_.append(QString::number(measurementSequence->coilAngle()));
    filename_.append("d");
    return filename_;
}


bool FileWriter::append(std::shared_ptr<DataPoint> datapoint){

    return true;
}

QString FileWriter::openFile(std::shared_ptr<MeasurementSequence> measurementSequence /*, QString filedir*/){

        QString path("SimulationsMessungen/");
        QDir dir;  // ich erstelle QString mit dem Ordner, danach die direction
        if (!dir.exists(path)) // Wenn nötig wird der Ordner erstellt
        dir.mkpath(path); // You can check the success if needed
        measurementSequence->setFileName(createFileName(measurementSequence));

        // der Filename und path wird gesezt, außerdem wird der name mit (i) verändert, wenn es die Txt datei schon  gibt
        QFile file(path + measurementSequence->fileName() + ".txt");
        for(int i=1; file.exists();i++)
        {
        if (file.exists()){
            file.setFileName(path + measurementSequence->fileName() +"_("+QString::number(i)+")" ".txt");
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

        return file.fileName();
}
