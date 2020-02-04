#include "classtestmanager.h"

#include <QDebug>


//Eigene Klassen
#include "../InduCore/filewriter.h"


ClassTestManager::ClassTestManager()
{

}

void ClassTestManager::startMeasurement(std::shared_ptr<MeasurementSequence> measurementsequence, QString filepath)
{
    FileWriter fw;




    fw.openFile(measurementsequence,filepath);

    qDebug()<<filepath;

}
