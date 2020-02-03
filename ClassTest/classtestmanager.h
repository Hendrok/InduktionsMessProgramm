#ifndef CLASSTESTMANAGER_H
#define CLASSTESTMANAGER_H

#include <memory>

#include "../InduControlCore/instrumentmanager.h"
#include "../InduCore/measurementsequence.h"

class ClassTestManager
{
public:
    ClassTestManager();
    void startMeasurement(std::shared_ptr<MeasurementSequence> measurementsequence);
private:

};

#endif // CLASSTESTMANAGER_H
