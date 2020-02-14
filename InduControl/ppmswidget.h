#ifndef PPPMSWIDGET_H
#define PPPMSWIDGET_H

#include <QWidget>

class DataPoint;
class QLineEdit;

class PpmsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PpmsWidget(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void newData(std::shared_ptr<const DataPoint> dpoint);

private:
    void createUI();

    //tempBlock
    QLineEdit* tempSetPoint_;
    QLineEdit* tempRate_;
    QLineEdit* tempStatus_;

    //MagBlock
    QLineEdit* magFeld_;
    QLineEdit* magSetPoint_;
    QLineEdit* magStatus_;

    //RotationBlock
    QLineEdit* rotSetPoint_;


};

#endif // PPPMSWIDGET_H
