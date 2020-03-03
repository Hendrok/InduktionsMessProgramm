#ifndef MEASUREMENTSTABLE_H
#define MEASUREMENTSTABLE_H
#include <QWidget>
#include <QListWidget>

//Internal Classes
class MeasurementSequence;

/* FIXME
 * - SetupUI() Method ist großgeschrieben
 * - In indumanager.h und instrumentmanager.h hast du jeweils
 *   eine Leerzeile nach Q_OBJECT.
 *   Bleib konsistent, mach es dann auch hier
 * - Dasselbe trifft auf den private:-Bereich zu:
 *   Hier hast du in den beiden anderen Dateien eine Leerzeile drüber
 * - in newMeasurement übergibst du den vector als Value-Type, kopierst ihne also
 *   Besser, als den gesamten Vector bei Methodenufruf zu kopieren, wäre es, ihn
 *   per Referenz zu übergeben:
 *
 *     const std::vector<std::shared_ptr<const MeasurementSequence>>&    gut
 *     std::vector<std::shared_ptr<const MeasurementSequence>>           schlecht, da kompletter
 *                                                                       vector kopiert wird
 * - Dasselbe Argument taucht in der activeMeasurement-Methode auf. Hier wird der shared_ptr
 *   kopiert
 */

class MeasurementsTable: public QWidget
{
     Q_OBJECT
public:
    explicit MeasurementsTable(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void newMeasurement(std::vector<std::shared_ptr<const MeasurementSequence> > mSeq);
    void activeMeasurement(std::shared_ptr<const MeasurementSequence> mesSeq);
private:
    void SetupUI();
    QListWidget *listWidget;
    std::vector<std::shared_ptr<const MeasurementSequence> > vecSeq_;
};

#endif // MEASUREMENTSTABLE_H
