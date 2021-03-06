#ifndef FILEWRITER_H
#define FILEWRITER_H

#include "InduCore_global.h"

#include <QString>
#include <memory>
#include <QFile>
#include <QObject>

//Internal Classes
class MeasSeqTc;
class MeasurementSequence;
class FileWriter;
class DataPoint;
#include "../InduControlCore/indumanager.h"

class INDUCORE_EXPORT FileWriter :QObject
{
    Q_OBJECT

public slots:

    void append(std::shared_ptr<DataPoint> datapoint);
public:
    FileWriter(QObject *parent =0);
    QString openFile(std::shared_ptr<const MeasurementSequence> measurementSequence);
    void closeFile();
    void MeasurementState(InduManager::State newState);


private:
    QString createFileName(std::shared_ptr<const MeasurementSequence> measurementSequence);
    QString writeHeader(std::shared_ptr<const MeasurementSequence> measurementSequence);
    QString filedir_;
    InduManager::State measurementState_;


    std::shared_ptr<QFile> file_;
};

#endif // FILEWRITER_H
