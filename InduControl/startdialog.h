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
    QWidget* widget;
    QWidget* widgetJc;
    std::vector <std::shared_ptr<const MeasurementSequence>> createSequence() const;
    QButtonGroup* buttongroupmes_;
    QRadioButton* tcbutton_;
    QRadioButton* jcbutton_;

    //Tc
    QLineEdit* sampleNameTc_;
    QDoubleSpinBox* tempStart_;
    QDoubleSpinBox* tempEnd_;
    QDoubleSpinBox* temperatureRate_;
    QDoubleSpinBox* magneticFieldTc_;
    QDoubleSpinBox* coilAngleTc_;
    QDoubleSpinBox* frequencyTc_;
    QDoubleSpinBox* voltageAmplitude_;
    QDoubleSpinBox* harmonicWaveTc_;

    //Jc
    QLineEdit* sampleNameJc_;
    QDoubleSpinBox* tempJc_;

    QDoubleSpinBox* coilAngleJc_;

private slots:
    void updateUI();
};

#endif // STARTDIALOG_H
