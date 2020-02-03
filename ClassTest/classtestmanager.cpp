#include "classtestmanager.h"
#include "../InduCore/filewriter.h"

#include <QDebug>
ClassTestManager::ClassTestManager()
{

}

void ClassTestManager::startMeasurement(std::shared_ptr<MeasurementSequence> measurementsequence)
{
    FileWriter fw;
    QString header =fw.writeHeader(measurementsequence);
    qDebug().noquote()<<header;

}
