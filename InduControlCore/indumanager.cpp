#include "indumanager.h"
#include <QDebug>
#include <QDir>
#include <memory>
#include "instrumentmanager.h"

//Eigene Klassen


InduManager::InduManager()
    :instrumentmanager_(new InstrumentManager())
    ,fw_(nullptr)
{
    connect(instrumentmanager_, &InstrumentManager::newData,
                this, &InduManager::onNewData);
}

InduManager::~InduManager()
{
    delete instrumentmanager_;
}

void InduManager::startMeasurement(std::shared_ptr<MeasurementSequence> &measurementSequence)
{
    fw_= std::make_unique<FileWriter>();
    fw_->openFile(measurementSequence);

    instrumentmanager_->onPolling();

}

void InduManager::onNewData(std::shared_ptr<DataPoint> datapoint)
{
    emit newData(datapoint);

        if (fw_ != nullptr)
        {
            fw_->append(datapoint);
        }

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
