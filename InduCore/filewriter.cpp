#include "filewriter.h"

#include <QString>
FileWriter::FileWriter(std::unique_ptr <MeasurementSequence> mfile )
    :mfile_(*mfile)
{

}

QString FileWriter::writeHeader(std::shared_ptr<MeasurementSequence> measurementSequence){
        //wasobenintextdateisteht später
      QString header_;
      header_="";
      header_.append(measurementSequence->supraName());
      header_.append("_");
      header_.append(QString::number(measurementSequence->voltageAmplitude()));
      header_.append("_");
      header_.append(QString::number(measurementSequence->frequency()));
      header_.append("_");
      header_.append(QString::number(measurementSequence->magneticField()));

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
