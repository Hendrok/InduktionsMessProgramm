#include "ppmswidget.h"

#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "../InduControlCore/indumanager.h"

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
    , voltageLive_(nullptr)
    , phaseLive_(nullptr)
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
        tempLive_->setText(QString::number(dpoint->ppmsdata()->pvTempLive()));
        magFieldLive_->setText(QString::number(dpoint->ppmsdata()->pvMagFieldLive()));
        rotLive_->setText(QString::number(dpoint->ppmsdata()->pvRotLive()));
        chamberLevel_->setText(QString::number(dpoint->ppmsdata()->pvChamberLevel()));
        voltageLive_->setText(QString::number(dpoint->ppmsdata()->pvVoltLive()));
        phaseLive_->setText(QString::number(dpoint->lockindata()->pvPhase()));
    }
    
}

void PpmsWidget::newMagSP(double magField, double magRate)
{
    magSetPoint_->setText(QString::number(magField));
    magRate_->setText(QString::number(magRate));

}

void PpmsWidget::newAngleSP(double angle)
{
    rotSetPoint_->setText(QString::number(angle));
}

void PpmsWidget::newTempSP(double temp, double rate)
{
    tempSetPoint_->setText(QString::number(temp));
    tempRate_->setText(QString::number(rate));
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
    magRate_ = new QLabel();
    magRate_->setText("");
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

    voltageLive_ = new QLabel();
    voltageLive_->setText("");
    phaseLive_ = new QLabel();
    phaseLive_->setText("");

    //label
    auto labelTempLive = new QLabel ("Temperature:");
    auto labelTempSetPoint = new QLabel ("Set Point:");
    auto labelTempRate = new QLabel ("Temp. Rate:");
    auto labelTempStatus = new QLabel ("Status:");

    auto labelMagFeldLive = new QLabel ("Mag. Field:");
    auto labelMagSetPoint = new QLabel ("Set Point:");
    auto labelMagRate = new QLabel ("Mag Rate:");
    auto labelMagStatus = new QLabel ("Status:");

    auto labelRotLive = new QLabel ("Rotation:");
    auto labelRotSetPoint = new QLabel ("Set Point:");
    auto labelRotStatus = new QLabel ("Status:");

    auto labelChamberLevel = new QLabel ("Helium Level:");
    auto labelChamberStatus = new QLabel ("Status:");

    auto labelVoltageLive = new QLabel ("Voltage:");
    auto labelPhaseLive = new QLabel ("Phase:");

    auto labelempty = new QLabel ("");

    //Grid Layouts:
    auto TempGridLayout = new QGridLayout();
    auto MagGridLayout = new QGridLayout();
    auto RotGridLayout = new QGridLayout();
    auto ChamberGridLayout = new QGridLayout();
    auto VoltageGridLayout = new QGridLayout();

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
    MagGridLayout->addWidget(labelMagRate, 2, 0);
    MagGridLayout->addWidget(magRate_, 2, 1);
    MagGridLayout->addWidget(labelMagStatus, 3, 0);
    MagGridLayout->addWidget(magStatus_, 3, 1);

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

    VoltageGridLayout->addWidget(labelVoltageLive, 0, 0);
    VoltageGridLayout->addWidget(voltageLive_, 0, 1);
    VoltageGridLayout->addWidget(phaseLive_, 1, 1);
    VoltageGridLayout->addWidget(labelPhaseLive, 1, 0);
    VoltageGridLayout->addWidget(labelempty, 2, 0);
    VoltageGridLayout->addWidget(labelempty, 2, 1);
    VoltageGridLayout->addWidget(labelempty, 3, 0);
    VoltageGridLayout->addWidget(labelempty, 3, 1);

    QWidget* tempWidget = new QWidget();
    tempWidget->setLayout(TempGridLayout);
    QWidget* magWidget = new QWidget();
    magWidget->setLayout(MagGridLayout);
    QWidget* rotWidget = new QWidget();
    rotWidget->setLayout(RotGridLayout);
    QWidget* chamberWidget = new QWidget();
    chamberWidget->setLayout(ChamberGridLayout);
    QWidget* voltageWidget = new QWidget();
    voltageWidget->setLayout(VoltageGridLayout);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(tempWidget);
    mainLayout->addWidget(magWidget);
    mainLayout->addWidget(rotWidget);
    mainLayout->addWidget(chamberWidget);
    mainLayout->addWidget(voltageWidget);
    setLayout(mainLayout);



}

