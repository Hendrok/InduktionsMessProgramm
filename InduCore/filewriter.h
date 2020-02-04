#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QString>
#include <memory>
#include <QFile>
#include "measurementsequence.h"
#include "InduCore_global.h"

//forward decleration (hier nur declariert, FileWriter ist z.B. declariert und definiert)
class DataPoint;

class INDUCORE_EXPORT FileWriter
{
public:
    FileWriter();
    QString openFile(std::shared_ptr<MeasurementSequence> measurementSequence, QString filepath);
    bool append(std::shared_ptr<DataPoint> datapoint);
    QString writeFileName(std::shared_ptr<MeasurementSequence> measurementSequence);

private:
    QString writeHeader(std::shared_ptr<MeasurementSequence> measurementSequence);



    MeasurementSequence mfile_;
    std::shared_ptr<QFile> file_;
};

#endif // FILEWRITER_H
