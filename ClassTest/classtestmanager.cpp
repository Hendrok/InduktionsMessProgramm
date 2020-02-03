#include "classtestmanager.h"

#include <QDebug>

//Eigene Klassen
#include "../InduCore/filewriter.h"


ClassTestManager::ClassTestManager()
{

}

void ClassTestManager::startMeasurement(std::shared_ptr<MeasurementSequence> measurementsequence)
{
    FileWriter fw;
    QString header = fw.writeHeader(measurementsequence);
    qDebug().noquote()<<header;

}
