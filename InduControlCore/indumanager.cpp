#include "indumanager.h"
#include <QDebug>
#include <QDir>
#include <memory>
#include "instrumentmanager.h"

//Eigene Klassen


InduManager::InduManager(){
}

InduManager::~InduManager()
{

}

void InduManager::startMeasurement(std::shared_ptr<MeasurementSequence> &measurementSequence, std::shared_ptr<DataPoint> &dataPoint)
{
    std::unique_ptr <FileWriter> fw= std::make_unique<FileWriter>();
    fw->openFile(measurementSequence);

    instrumentmanager_ = new InstrumentManager();

    connect(instrumentmanager_,SIGNAL(instrumentmanager_->newData),
            this,SLOT(append(dataPoint)));
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
