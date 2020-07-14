#ifndef STATUS_H
#define STATUS_H
#include "Instruments_global.h"
#include "gpib.h"


#include <QObject>

class INSTRUMENTS_EXPORT Status:public QObject
{
    Q_OBJECT
public:
    void gpibStatus(GPIB gpib);
signals:
    void newGpibStatus();
};

#endif // STATUS_H
