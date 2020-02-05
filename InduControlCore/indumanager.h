#ifndef INDUMANAGER_H
#define INDUMANAGER_H
#include "InduControlCore_global.h"
#include <memory>

//Eigene Klassen
#include "instrumentmanager.h"
#include "../InduCore/measurementsequence.h"
#include "../InduCore/datapoint.h"
#include "../InduCore/filewriter.h"
#include "../InduCore/datafile.h"
#include "instrumentmanager.h"
class INDUCONTROLCORE_EXPORT InduManager
{
public:
    InduManager();
    void startMeasurement(std::shared_ptr<MeasurementSequence> &measurementSequence, std::shared_ptr<DataPoint> &dataPoint);
    //void startAppending(std::shared_ptr<MeasurementSequence> &measurementSequence, std::shared_ptr<DataPoint> &dataPoint);
private:
    std::unique_ptr<InstrumentManager> instrumentmanager_;


};

#endif // INDUMANAGER_H
