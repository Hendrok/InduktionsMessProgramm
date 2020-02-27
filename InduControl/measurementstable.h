#ifndef MEASUREMENTSTABLE_H
#define MEASUREMENTSTABLE_H
#include <QWidget>
#include <QListWidget>

//Internal Classes
class MeasurementSequence;

class MeasurementsTable: public QWidget
{
     Q_OBJECT
public:
    explicit MeasurementsTable(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void newMeasurement(std::vector<std::shared_ptr<const MeasurementSequence> > mSeq);
private:
    void SetupUI();
    QListWidget *listWidget;

};

#endif // MEASUREMENTSTABLE_H
