#include "indumanager.h"
#include <QDebug>


//Eigene Klassen
#include "../InduCore/filewriter.h"
#include "../InduCore/measurementsequence.h"
#include <QDir>
InduManager::InduManager()
{

}

void InduManager::startMeasurement(std::shared_ptr<MeasurementSequence> measurementSequence)
{
    FileWriter fw;
    fw.openFile(measurementSequence);
}
