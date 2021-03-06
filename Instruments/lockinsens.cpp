#include "lockinsens.h"
#include "QDebug"
#include "../InduCore/datapoint.h"

LockInSens::LockInSens()
    : refVoltage_(0)
    , sensState_(0)
    , sensitivity_(Sensitivity(sensState_))
{
}

int LockInSens::setSensitivity(std::shared_ptr<DataPoint> datapoint)
{
    if(datapoint->lockindata()->pvVoltOutputLive() > refVoltage_*0.9 && sensState_ != 26)
    {
        sensState_++;
        sensitivity_ = Sensitivity(sensState_);
        setRefVoltage();

    }
    if(datapoint->lockindata()->pvVoltOutputLive() < refVoltage_/2.5 && sensState_ !=0)
    {
        sensState_--;
        sensitivity_ = Sensitivity(sensState_);
        setRefVoltage();

    }
    /*qDebug()<<datapoint->lockindata()->pvVoltOutputLive();
    qDebug()<<sensState_;*/
    return sensState_;
}

void LockInSens::setRefVoltage()
{

    switch (sensitivity_)
    {
    case Sensitivity::NanoVolt2:{refVoltage_ =    0.000000002; break;}
    case Sensitivity::NanoVolt5:{refVoltage_ =    0.000000005; break;}
    case Sensitivity::NanoVolt10:{refVoltage_ =   0.00000001; break;}
    case Sensitivity::NanoVolt20:{refVoltage_ =   0.00000002; break;}
    case Sensitivity::NanoVolt50:{refVoltage_ =   0.00000005; break;}
    case Sensitivity::NanoVolt100:{refVoltage_ =  0.0000001; break;}
    case Sensitivity::NanoVolt200:{refVoltage_ =  0.0000002; break;}
    case Sensitivity::NanoVolt500:{refVoltage_ =  0.0000005; break;}
    case Sensitivity::MicroVolt1:{refVoltage_ =   0.000001; break;}
    case Sensitivity::MicroVolt2:{refVoltage_ =   0.000002; break;}
    case Sensitivity::MicroVolt5:{refVoltage_ =   0.000005; break;}
    case Sensitivity::MicroVolt10:{refVoltage_ =  0.00001; break;}
    case Sensitivity::MicroVolt20:{refVoltage_ =  0.00002; break;}
    case Sensitivity::MicroVolt50:{refVoltage_ =  0.00005; break;}
    case Sensitivity::MicroVolt100:{refVoltage_ = 0.0001; break;}
    case Sensitivity::MicroVolt200:{refVoltage_ = 0.0002; break;}
    case Sensitivity::MicroVolt500:{refVoltage_ = 0.0005; break;}
    case Sensitivity::MilliVolt1:{refVoltage_ =   0.001; break;}
    case Sensitivity::MilliVolt2:{refVoltage_ =   0.002; break;}
    case Sensitivity::MilliVolt5:{refVoltage_ =   0.005; break;}
    case Sensitivity::MilliVolt10:{refVoltage_ =  0.01; break;}
    case Sensitivity::MilliVolt20:{refVoltage_ =  0.02; break;}
    case Sensitivity::MilliVolt50:{refVoltage_ =  0.05; break;}
    case Sensitivity::MilliVolt100:{refVoltage_ = 0.1; break;}
    case Sensitivity::MilliVolt200:{refVoltage_ = 0.2; break;}
    case Sensitivity::MilliVolt500:{refVoltage_ = 0.5; break;}
    case Sensitivity::Volt1:{refVoltage_ =        1; break;}
    }   
}
