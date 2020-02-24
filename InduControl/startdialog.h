#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include <QRadioButton>

class MeasSeqTc;
class MeasurementSequence;
class QDoubleSpinBox;
class QLineEdit;
class StartDialog : public QDialog
{
    Q_OBJECT

signals:
    void createMeasurement(std::vector <std::shared_ptr<const MeasurementSequence>>);

public:
    explicit StartDialog(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected:
    void accept() override;

private:
    void setupUI();
    void clearwidgets(QLayout * layout);
    std::vector <std::shared_ptr<const MeasurementSequence>> createSequence() const;
    QButtonGroup* buttongroupmes_;
    QRadioButton* tcbutton_;
    QRadioButton* jcbutton_;
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
