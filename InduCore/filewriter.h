#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QString>
#include <memory>

#include "InduCore_global.h"

//forward decleration (hier nur declariert, FileWriter ist z.B. declariert und definiert)
class INDUCORE_EXPORT MeasurementSequence;
class DataPoint;

class FileWriter
{
public:
    FileWriter();
    QString openFile(std::shared_ptr<MeasurementSequence> measurementSequence, QString filepath);
    bool append(std::shared_ptr<DataPoint> datapoint);
private:
    bool writeHeader(std::shared_ptr<MeasurementSequence> measurementSequence);

};

#endif // FILEWRITER_H
