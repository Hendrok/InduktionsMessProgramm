#include "indumanager.h"
#include <QDebug>
#include <QDir>
#include <memory>


//Eigene Klassen




InduManager::InduManager()
{
}

void InduManager::startMeasurement(std::shared_ptr<MeasurementSequence> &measurementSequence, std::shared_ptr<DataPoint> &dataPoint)
{
    std::unique_ptr <FileWriter> fw= std::make_unique<FileWriter>();
    fw->openFile(measurementSequence);
    InstrumentManager* Im = new InstrumentManager();
    Im->onPolling();
    fw->append(dataPoint);

}

/*void InduManager::startAppending(std::shared_ptr<MeasurementSequence> &measurementSequence, std::shared_ptr<DataPoint> &dataPoint)
{

    for(double Temp=measurementSequence->tempStart();Temp<measurementSequence->tempEnd();Temp=Temp+0.1)
    {
        dataPoint->setpvTemp(Temp);
        dataPoint->setpvVolt(30);
        dataPoint->setpvPhase(180);

        fw.append(dataPoint);
    }

}
*/
