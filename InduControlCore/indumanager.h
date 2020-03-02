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


class INDUCONTROLCORE_EXPORT InduManager: public QObject
=======
/* FIXME
 * - Forward Declaration von PpmsSimulation ist unnötig
 * - In den Attributen sind bei den Smart Pointern 4 Leerzeichen zu viel
 * - Typ vo measurementNumber_ sollte eher size_t sein, und nicht unsigned long
 *   Zum einen soll man unsigned Datentypen vermeiden, zum anderen soll man long
 *   vermeiden. Unsigned long ist doppelt schlimm :-D
 *   Du greifst mit der Variable measurementNumber_ auf die Elemente eines
 *   std::vectors zu, der korrekte Typ hierfür ist size_t
 * - In der Deklaration von appendMeasurement ist ein Leerzeichen zu viel
 * - Inkonsistenz zwischen diesem Header und instrumentmanager.h:
 *     Hier hast du nach Q_OBJECT eine Leerzeile, in instrumentmanager.h nicht
 *     Ich finde diese Version hier besser. Wie auch immer du dich entscheiden solltest,
 *     halte den Stil über alle Dateien konsistent bei
 * - Ein Leerzeichen zu wenig bei: class ... InduManager :public Object
 */

class INDUCONTROLCORE_EXPORT InduManager :public QObject

{
    Q_OBJECT

public:
    explicit InduManager();
    ~InduManager();
    enum class State { Idle, ApproachStartTc, ApproachEndTc, CheckForMeas, ApproachStartJc, ApproachEndJc};
    void appendMeasurement(std::vector<std::shared_ptr<const MeasurementSequence>> mVecSeq);
    void startMeasurement(std::shared_ptr<const MeasurementSequence> measurementSequence);

signals:
    void newData(std::shared_ptr<const DataPoint>);
    void startNewMeasurement(std::shared_ptr<const MeasurementSequence>);
    void newState(State newState);

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
};

#endif // INDUMANAGER_H
