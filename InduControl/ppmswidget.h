#ifndef PPPMSWIDGET_H
#define PPPMSWIDGET_H

#include <QWidget>

//Internal Classes
class DataPoint;
class QLabel;
class InstrumentManager;

class PpmsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PpmsWidget(QWidget *parent = nullptr);


    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void newData(std::shared_ptr<const DataPoint> dpoint);
    void newMagSP(double magField, double magRate);
    void newAngleSP(double angle);
    void newTempSP(double temp, double rate);
private:
    void setupUI();
    //tempBlock
    QLabel* tempSetPoint_;
    QLabel* tempLive_;
    QLabel* tempRate_;
    QLabel* tempStatus_;

    //MagBlock
    QLabel* magSetPoint_;
    QLabel* magFieldLive_;
    QLabel* magRate_;
    QLabel* magStatus_;

    //RotationBlock
    QLabel* rotSetPoint_;
    QLabel* rotLive_;
    QLabel* rotStatus_;

    //Chamber
    QLabel* chamberStatus_;
    QLabel* chamberLevel_;

    //Lockin
    QLabel* voltageLive_;
    QLabel* phaseLive_;

    QString tempStatStr_;
    QString magStatStr_;
    QString chambStatStr_;
    QString rotStatStr_;


};

#endif // PPPMSWIDGET_H
