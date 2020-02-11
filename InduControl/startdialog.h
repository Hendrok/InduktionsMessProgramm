#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>

class MeasurementSequence;
class QDoubleSpinBox;

class StartDialog : public QDialog
{
    Q_OBJECT

signals:
    void startMeasurement(std::shared_ptr<const MeasurementSequence>);

public:
    explicit StartDialog(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected:
    void accept() override;

private:
    void setupUI();
    std::shared_ptr<const MeasurementSequence> createSequence() const;

    QDoubleSpinBox* tempStart_;
    QDoubleSpinBox* tempEnd_;
};

#endif // STARTDIALOG_H
