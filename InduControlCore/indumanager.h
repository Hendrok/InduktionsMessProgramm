#ifndef INDUMANAGER_H
#define INDUMANAGER_H
#include "InduControlCore_global.h"
#include <memory>

//Eigene Klassen
#include "instrumentmanager.h"
#include "../InduCore/measurementsequence.h"

class INDUCONTROLCORE_EXPORT InduManager
{
public:
    InduManager();
    void startMeasurement(std::shared_ptr<MeasurementSequence> measurementSequence);
private:
    std::unique_ptr<InstrumentManager> instrumentmanager_;
};

#endif // INDUMANAGER_H
