#ifndef MEASUREMENTSTABLE_H
#define MEASUREMENTSTABLE_H
#include <QWidget>
#include <QListWidget>

//Internal Classes
class MeasurementSequence;

/* FIXME

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
    void setupUI();
    QListWidget *listWidget;
    std::vector<std::shared_ptr<const MeasurementSequence>> vecSeq_;
};

#endif // MEASUREMENTSTABLE_H
