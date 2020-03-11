#ifndef LOCKINSENS_H
#define LOCKINSENS_H
#include "Instruments_global.h"
#include <QObject>
#include <memory>

class DataPoint;

class INSTRUMENTS_EXPORT LockInSens: public QObject
{
    Q_OBJECT
public:
    LockInSens();
public:
    enum class Sensitivity
    {
      NanoVolt2,
      NanoVolt5,
      NanoVolt10,
      NanoVolt20,
      NanoVolt50,
      NanoVolt100,
      NanoVolt200,
      NanoVolt500,
      MicroVolt1,
      MicroVolt2,
      MicroVolt5,
      MicroVolt10,
      MicroVolt20,
      MicroVolt50,
      MicroVolt100,
      MicroVolt200,
      MicroVolt500,
      MilliVolt1,
      MilliVolt2,
      MilliVolt5,
      MilliVolt10,
      MilliVolt20,
      MilliVolt50,
      MilliVolt100,
      MilliVolt200,
      MilliVolt500,
      Volt1
    };
public slots:
    void setSensitivity(std::shared_ptr<DataPoint> datapoint);
private:
    Sensitivity sensitivity_;

};





#endif // LOCKINSENS_H
