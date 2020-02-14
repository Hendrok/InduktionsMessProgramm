#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>

class MeasSeqTc;
class QDoubleSpinBox;
class QLineEdit;
class StartDialog : public QDialog
{
    Q_OBJECT

signals:
    void startMeasurement(std::shared_ptr<const MeasSeqTc>);

public:
    explicit StartDialog(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected:
    void accept() override;

private:
    void setupUI();
    std::shared_ptr<const MeasSeqTc> createSequence() const;

    QLineEdit* sampleName_;
    QDoubleSpinBox* tempStart_;
    QDoubleSpinBox* tempEnd_;
    QDoubleSpinBox* temperatureRate_;
    QDoubleSpinBox* magneticField_;
    QDoubleSpinBox* coilAngle_;
    QDoubleSpinBox* frequency_;
    QDoubleSpinBox* voltageAmplitude_;
    QDoubleSpinBox* harmonicWave_;

};

#endif // STARTDIALOG_H
