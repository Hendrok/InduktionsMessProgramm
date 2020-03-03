#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include <QRadioButton>

//Internal Classes
class MeasSeqTc;
class MeasurementSequence;
class QDoubleSpinBox;
class QLineEdit;


/* FIXME
 * - createMeasurement-Signal und CreateSequence-Methode erzeugen jeweils eine Kopie von
 *   dem Vector. Bis die Shared-Ptr also im InduManager ankommen, wurden sie schon insgesamt
 *   2x unnötig kopiert. Schau dazu mal in die Diskussion von measurementstable.h
 */
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
    QWidget* widgetTc;
    QWidget* widgetJc;
    std::vector <std::shared_ptr<const MeasurementSequence>> createSequence() const;
    QButtonGroup* buttongroupmes_;
    QRadioButton* tcbutton_;
    QRadioButton* jcbutton_;

    //Tc
    QLineEdit* sampleNameTc_;
    QDoubleSpinBox* tempStartTc_;
    QDoubleSpinBox* tempEndTc_;
    QDoubleSpinBox* temperatureRateTc_;
    QDoubleSpinBox* magneticFieldTc_;
    QDoubleSpinBox* coilAngleTc_;
    QDoubleSpinBox* frequencyTc_;
    QDoubleSpinBox* voltageAmplitudeTc_;
    QDoubleSpinBox* harmonicWaveTc_;

    //Jc
    QLineEdit* sampleNameJc_;
    QDoubleSpinBox* tempJc_;
    QDoubleSpinBox* frequencyJc_;
    QDoubleSpinBox* magneticFieldJc_;
    QDoubleSpinBox* voltStartJc_;
    QDoubleSpinBox* voltEndJc_;
    QDoubleSpinBox* VoltRateJc_;
    QDoubleSpinBox* coilAngleJc_;
    QDoubleSpinBox* harmonicWaveJc_;

private slots:
    void updateUI();
};

#endif // STARTDIALOG_H
