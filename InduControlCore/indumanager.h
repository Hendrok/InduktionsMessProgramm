#ifndef INDUMANAGER_H
#define INDUMANAGER_H
#include "InduControlCore_global.h"
#include <memory>
#include <QObject>
#include <vector>

//Internal Classes
class MeasSeqTc;
class MeasSeqJc;
class MeasurementSequence;
class DataPoint;
class FileWriter;
class InstrumentManager;

class INDUCONTROLCORE_EXPORT InduManager : public QObject
{
    Q_OBJECT

public:
    explicit InduManager();
    ~InduManager();
    void openDevice();
    enum class State { Idle, ApproachStartTc, ApproachEndTc, CheckForMeas, ApproachStartJc, ApproachEndJc};
    void appendMeasurement(std::vector<std::shared_ptr<const MeasurementSequence>> mVecSeq);
    void startMeasurement(std::shared_ptr<const MeasurementSequence> measurementSequence);
    void rotatorState(bool rotator);

signals:
    void newData(std::shared_ptr<const DataPoint>);
    void startNewMeasurement(std::shared_ptr<const MeasurementSequence>);
    void newState(State newState);
    void newTempSP(double setpoint, double rate);
    void newMagSP(double magField, double magRate);
    void newAngleSP(double angle);
    void newFreqSP(double freq);
    void newSensivitySP(int sensivity);
    void newHarmonicSP(int harmonicW);
    void newRotstate(bool rotActive);
    void newErrorMessage(QString errormessagePpms);

private slots:
    void onNewData(std::shared_ptr<DataPoint> datapoint);

private:
    size_t measurementNumber_;
    std::vector<std::shared_ptr<const MeasurementSequence> > mVecSeq_;
    std::unique_ptr <InstrumentManager> instrumentmanager_;
    std::unique_ptr <FileWriter> fw_;
    std::shared_ptr <MeasSeqTc> mSeqTc_;
    std::shared_ptr <MeasSeqJc> mSeqJc_;
    State measurementState;
    double magFieldSP_;
    double angleSP_;
    double tempSP_;
};

#endif // INDUMANAGER_H
