#include "filewriter.h"

#include <QString>
FileWriter::FileWriter(MeasurementSequence &mfile)
    :mfile_(mfile)
{

}

bool FileWriter::writeHeader(std::shared_ptr<MeasurementSequence> measurementSequence){
        //wasobenintextdateisteht später
      QString header_;
      header_="";
      header_.append(measurementSequence->supraName());
      header_.append("_");
      header_.append(QString::number(measurementSequence->VoltageAmplitude()));
      header_.append("_");
      header_.append(QString::number(measurementSequence->Frequency()));
      header_.append("_");
      header_.append(QString::number(measurementSequence->MagneticField()));

if (header_==""){
    return false;
}
else{
    return true;
}
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
