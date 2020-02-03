#ifndef INDUMANAGER_H
#define INDUMANAGER_H
#include "InduControlCore_global.h"
#include <memory>

#include "../InduCore/measurementsequence.h"

class INDUCONTROLCORE_EXPORT InduManager
{
public:
    InduManager();
    void startMeasurement(std::shared_ptr<MeasurementSequence>);
};

#endif // INDUMANAGER_H
