#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QString>
#include <memory>
#include <QFile>
#include <QObject>

#include "InduCore_global.h"

//forward decleration (hier nur declariert, FileWriter ist z.B. declariert und definiert)
class MeasSeqTc;
class MeasurementSequence;
class FileWriter;
class DataPoint;


class INDUCORE_EXPORT FileWriter :QObject
{
    Q_OBJECT

public slots:

    bool append(std::shared_ptr<DataPoint> datapoint);
public:
    FileWriter(QObject *parent =0);
    QString openFile(std::shared_ptr<const MeasurementSequence> measurementSequence/*, QString filedir*/);
    //bool append(std::shared_ptr<DataPoint> datapoint);


private:
    QString createFileName(std::shared_ptr<const MeasurementSequence> measurementSequence);
    QString writeHeader(std::shared_ptr<const MeasurementSequence> measurementSequence);
    QString filedir_;



    std::shared_ptr<QFile> file_;
};

#endif // FILEWRITER_H
