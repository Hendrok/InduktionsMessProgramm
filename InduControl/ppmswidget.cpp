#include "ppmswidget.h"
#include "../InduCore/datapoint.h"

#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

PpmsWidget::PpmsWidget(QWidget *parent)
    : QWidget (parent)
    , tempSetPoint_(nullptr)
    , tempLive_ (nullptr)
    , tempRate_ (nullptr)
    , tempStatus_(nullptr)
    , magSetPoint_(nullptr)
    , magFieldLive_ (nullptr)
    , magStatus_ (nullptr)
    , rotSetPoint_(nullptr)
    , rotLive_ (nullptr)
    , rotStatus_(nullptr)
    , chamberStatus_(nullptr)
    , chamberLevel_(nullptr)
{    
    setupUI();
}

QSize PpmsWidget::sizeHint() const
{
    return QSize(1800,300);
}

QSize PpmsWidget::minimumSizeHint() const
{
    return QSize(400,50);
}

void PpmsWidget::newData(std::shared_ptr<const DataPoint> dpoint)
{
    if(dpoint != nullptr){
        tempLive_->setText(QString::number(dpoint->pvTemp()));
        magFieldLive_->setText(QString::number(dpoint->pvField()));
        rotLive_->setText(QString::number(dpoint->pvAngle()));
    }
    
}

void PpmsWidget::setupUI()
{
    tempLive_ = new QLabel();
    tempLive_->setText("");
    tempSetPoint_ = new QLabel();
    tempSetPoint_->setText("");
    tempRate_ = new QLabel();
    tempRate_->setText("");
    tempStatus_ = new QLabel();
    tempStatus_->setText("");

    magSetPoint_ = new QLabel();
    magSetPoint_->setText("");
    magFieldLive_ = new QLabel();
    magFieldLive_->setText("");
    magStatus_ = new QLabel();
    magStatus_->setText("");

    rotLive_ = new QLabel();
    rotLive_->setText("");
    rotSetPoint_ = new QLabel();
    rotSetPoint_->setText("");
    rotStatus_ = new QLabel();
    rotStatus_->setText("");

    chamberStatus_ = new QLabel();
    chamberStatus_->setText("");
    chamberLevel_ = new QLabel();
    chamberLevel_->setText("");

    //label
    QLabel* labelTempLive = new QLabel ("Temperature:");
    QLabel* labelTempSetPoint = new QLabel ("Set Point:");
    QLabel* labelTempRate = new QLabel ("Temp. Rate:");
    QLabel* labelTempStatus = new QLabel ("Status:");

    QLabel* labelMagFeldLive = new QLabel ("Mag. Field:");
    QLabel* labelMagSetPoint = new QLabel ("Set Point:");
    QLabel* labelMagStatus = new QLabel ("Status:");

    QLabel* labelRotLive = new QLabel ("Rotation:");
    QLabel* labelRotSetPoint = new QLabel ("SetPoint:");
    QLabel* labelRotStatus = new QLabel ("Status:");

    QLabel* labelChamberLevel = new QLabel ("Helium Level:");
    QLabel* labelChamberStatus = new QLabel ("Status:");
    QLabel* labelempty = new QLabel ("");

    //Grid Layouts:
    QGridLayout* TempGridLayout = new QGridLayout();
    QGridLayout* MagGridLayout = new QGridLayout();
    QGridLayout* RotGridLayout = new QGridLayout();
    QGridLayout* ChamberGridLayout = new QGridLayout();

    TempGridLayout->addWidget(labelTempLive, 0, 0);
    TempGridLayout->addWidget(tempLive_, 0, 1);
    TempGridLayout->addWidget(labelTempSetPoint, 1, 0);
    TempGridLayout->addWidget(tempSetPoint_ , 1, 1);
    TempGridLayout->addWidget(labelTempRate, 2, 0);
    TempGridLayout->addWidget(tempRate_, 2, 1);
    TempGridLayout->addWidget(labelTempStatus, 3, 0);
    TempGridLayout->addWidget(tempStatus_, 3, 1);

    MagGridLayout->addWidget(labelMagFeldLive, 0, 0);
    MagGridLayout->addWidget(magFieldLive_, 0, 1);
    MagGridLayout->addWidget(labelMagSetPoint, 1, 0);
    MagGridLayout->addWidget(magSetPoint_ , 1, 1);
    MagGridLayout->addWidget(labelMagStatus, 2, 0);
    MagGridLayout->addWidget(magStatus_, 2, 1);
    MagGridLayout->addWidget(labelempty, 3, 0);
    MagGridLayout->addWidget(labelempty, 3, 1);

    RotGridLayout->addWidget(labelRotLive, 0, 0);
    RotGridLayout->addWidget(rotLive_, 0, 1);
    RotGridLayout->addWidget(labelRotSetPoint, 1, 0);
    RotGridLayout->addWidget(rotSetPoint_ , 1, 1);
    RotGridLayout->addWidget(labelRotStatus, 2, 0);
    RotGridLayout->addWidget(rotStatus_, 2, 1);
    RotGridLayout->addWidget(labelempty, 3, 0);
    RotGridLayout->addWidget(labelempty, 3, 1);

    ChamberGridLayout->addWidget(labelChamberLevel, 0, 0);
    ChamberGridLayout->addWidget(chamberLevel_, 0, 1);
    ChamberGridLayout->addWidget(labelChamberStatus, 1, 0);
    ChamberGridLayout->addWidget(chamberStatus_ , 1, 1);
    ChamberGridLayout->addWidget(labelempty, 2, 0);
    ChamberGridLayout->addWidget(labelempty, 2, 1);
    ChamberGridLayout->addWidget(labelempty, 3, 0);
    ChamberGridLayout->addWidget(labelempty, 3, 1);

    QWidget* tempWidget = new QWidget();
    tempWidget->setLayout(TempGridLayout);
    QWidget* magWidget = new QWidget();
    magWidget->setLayout(MagGridLayout);
    QWidget* rotWidget = new QWidget();
    rotWidget->setLayout(RotGridLayout);
    QWidget* chamberWidget = new QWidget();
    chamberWidget->setLayout(ChamberGridLayout);


    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(tempWidget);
    mainLayout->addWidget(magWidget);
    mainLayout->addWidget(rotWidget);
    mainLayout->addWidget(chamberWidget);
    setLayout(mainLayout);



}

