#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QString>
#include <memory>
#include <QFile>
#include "measurementsequence.h"
#include "InduCore_global.h"
#include "../InduCore/datapoint.h"
#include <QObject>

//forward decleration (hier nur declariert, FileWriter ist z.B. declariert und definiert)
class DataPoint;

class INDUCORE_EXPORT FileWriter :QObject
{
    Q_OBJECT

public slots:
    void receiveData(std::shared_ptr<DataPoint> datapoint);
public:
    FileWriter();
    QString openFile(std::shared_ptr<MeasurementSequence> measurementSequence/*, QString filedir*/);
    bool append(std::shared_ptr<DataPoint> datapoint);


private:
    QString createFileName(std::shared_ptr<MeasurementSequence> measurementSequence);
    QString writeHeader(std::shared_ptr<MeasurementSequence> measurementSequence);
    QString filedir_;



    std::shared_ptr<QFile> file_;
};

#endif // FILEWRITER_H
