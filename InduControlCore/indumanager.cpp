#include "indumanager.h"
#include <QDebug>
#include <QDir>
#include <memory>
#include "instrumentmanager.h"


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


