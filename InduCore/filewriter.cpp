#include "filewriter.h"

#include <QString>
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
      header_.append("\n Frequency: ");
      header_.append(QString::number(measurementSequence->frequency()));
      header_.append("\n Magnetic Field: ");
      header_.append(QString::number(measurementSequence->magneticField()));
      header_.append("\n Starting Temperature: ");
      header_.append(QString::number(measurementSequence->tempStart()));
      header_.append("\n Ending Temperature: ");
      header_.append(QString::number(measurementSequence->tempEnd()));
      header_.append("\n Temperature Rate: ");
      header_.append(QString::number(measurementSequence->temperatureRate()));
      header_.append("\n Harmonic Wave: ");
      header_.append(QString::number(measurementSequence->harmonicWave()));
      header_.append("\n CoilAngle: ");
      header_.append(QString::number(measurementSequence->coilAngle()));
      header_.append("\n");

/*if (header_==""){
    return false;
}
else{
    return true;
}*/
      return header_;
}

bool FileWriter::append(std::shared_ptr<DataPoint> datapoint){

    return true;
}

QString FileWriter::openFile(std::shared_ptr<MeasurementSequence> measurementSequence, QString filepath){


        file_ = std::make_shared<QFile>(filepath);
        file_->open(QIODevice::WriteOnly | QIODevice::Text);

        if(!file_->isOpen())
        {
            return QString();
        }

        writeHeader(measurementSequence);

        return filepath;
}
