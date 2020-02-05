#include "indumanager.h"
#include <QDebug>
#include <QDir>
#include <memory>

//Eigene Klassen




InduManager::InduManager()
{

}

void InduManager::startMeasurement(std::shared_ptr<MeasurementSequence> &measurementSequence)
{

    fw.openFile(measurementSequence);
    InstrumentManager Im(measurementSequence);
    Im.createRandomDataPoints();

}

void InduManager::startAppending(std::shared_ptr<MeasurementSequence> &measurementSequence, std::shared_ptr<DataPoint> &dataPoint)
{

    for(double Temp=measurementSequence->tempStart();Temp<measurementSequence->tempEnd();Temp=Temp+0.1)
    {
        dataPoint->setpvTemp(Temp);
        dataPoint->setpvVolt(30);
        dataPoint->setpvPhase(180);

        fw.append(dataPoint);
    }

}
