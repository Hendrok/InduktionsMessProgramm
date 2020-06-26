#include "ppmswidget.h"

#include <QDebug>
#include <vector>
#include <locale>
#include <sstream>
#include <iomanip>
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
    , sampleSpacePressure_(nullptr)
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
        tempStatus_->setText(tempStatStr_);
        magFieldLive_->setText(QString::number(dpoint->ppmsdata()->pvMagFieldLive()));
        rotLive_->setText(QString::number(dpoint->ppmsdata()->pvRotLive()));
        chamberLevel_->setText(QString::number(dpoint->ppmsdata()->pvChamberLevel()));
        sampleSpacePressure_->setText(QString::number(dpoint->ppmsdata()->pvSamplePressure()));
        voltageLive_->setText(QString::number(dpoint->lockindata()->pvVoltOutputLive()));
        phaseLive_->setText(QString::number(dpoint->lockindata()->pvPhase()));

        QString ppmsStatusStr = QString::fromStdString(dpoint->ppmsdata()->pvStatusPpms());
        auto ppmsStatus = ppmsStatusStr.toDouble();
        /*Kurze Erklärung: es wird auf die 3te Zahl zugegriffen und dann mit den & operator geguckt wo sich die Binärzahlen unterscheiden/gleichen
        *die ersten 4 Zahlen (also 0->15) sind die erste if abfrage usw.
        */
          if ((static_cast<int>(ppmsStatus) & 0b1111) == 0) { tempStatus_->setText("Status unknown"); }
          else if ((static_cast<int>(ppmsStatus) & 0b1111) == 1) { tempStatus_->setText("Stable"); }
          else if ((static_cast<int>(ppmsStatus) & 0b1111) == 2) { tempStatus_->setText("Tracking"); }
          else if ((static_cast<int>(ppmsStatus) & 0b1111) == 3) { tempStatus_->setText("Reserved"); }
          else if ((static_cast<int>(ppmsStatus) & 0b1111) == 4) { tempStatus_->setText("Reserved"); }
          else if ((static_cast<int>(ppmsStatus) & 0b1111) == 5) { tempStatus_->setText("Near"); }
          else if ((static_cast<int>(ppmsStatus) & 0b1111) == 6) { tempStatus_->setText("Chasing"); }
          else if ((static_cast<int>(ppmsStatus) & 0b1111) == 7) { tempStatus_->setText("Filling/Emptying reservoir"); }
          else if ((static_cast<int>(ppmsStatus) & 0b1111) == 8) { tempStatus_->setText("Reserved"); }
          else if ((static_cast<int>(ppmsStatus) & 0b1111) == 9) { tempStatus_->setText("Reserved"); }
          else if ((static_cast<int>(ppmsStatus) & 0b1111) == 10) { tempStatus_->setText("Stand By Mode"); }
          else if ((static_cast<int>(ppmsStatus) & 0b1111) == 11) { tempStatus_->setText("Reserved"); }
          else if ((static_cast<int>(ppmsStatus) & 0b1111) == 12) { tempStatus_->setText("Reserved"); }
          else if ((static_cast<int>(ppmsStatus) & 0b1111) == 13) { tempStatus_->setText("temperature Control disabled"); }
          else if ((static_cast<int>(ppmsStatus) & 0b1111) == 14) { tempStatus_->setText("Impedance not functioning"); }
          else if ((static_cast<int>(ppmsStatus) & 0b1111) == 15) { tempStatus_->setText("General Failure"); }
          //Feld-Stati
          if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 0) { magStatus_->setText("Status unknown"); }
          else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 1) { magStatus_->setText("Persistent mode, stable"); }
          else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 2) { magStatus_->setText("Persist mode switch warming"); }
          else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 3) { magStatus_->setText("Persist mode switch cooling"); }
          else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 4) { magStatus_->setText("Driven mode, stable at final field"); }
          else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 5) { magStatus_->setText("Driven mode, final approach"); }
          else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 6) { magStatus_->setText("Charging magnet at specified voltage"); }
          else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 7) { magStatus_->setText("Discharging magnet"); }
          else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 8) { magStatus_->setText("Current error, incorrect current in magnet"); }
          else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 9) { magStatus_->setText("Reserved"); }
          else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 10) { magStatus_->setText("Reserved"); }
          else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 11) { magStatus_->setText("Reserved"); }
          else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 12) { magStatus_->setText("Reserved"); }
          else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 13) { magStatus_->setText("Reserved"); }
          else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 14) { magStatus_->setText("Reserved"); }
          else if (((static_cast<int>(ppmsStatus) >> 4) & 0b1111) == 15) { magStatus_->setText("General failure in magnet control system"); }
          //Chamber-Stati
          if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 0) { chamberStatus_->setText("Status unknown"); }
          else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 1) { chamberStatus_->setText("Purged and sealed"); }
          else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 2) { chamberStatus_->setText("Vented and sealed"); }
          else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 3) { chamberStatus_->setText("Sealed, condition unknown"); }
          else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 4) { chamberStatus_->setText("Performing purge/seal routine"); }
          else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 5) { chamberStatus_->setText("Performing vent/seal sequence"); }
          else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 6) { chamberStatus_->setText("Reserved"); }
          else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 7) { chamberStatus_->setText("Reserved"); }
          else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 8) { chamberStatus_->setText("Pumping continuously"); }
          else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 9) { chamberStatus_->setText("Flooding continuously"); }
          else if (((static_cast<int>(ppmsStatus) >> 8) & 0b1111) == 15) { chamberStatus_->setText("General failure in gas control System"); }
          //angle
          if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 0) { rotStatus_->setText("Status unknown"); }
          else if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 1) { rotStatus_->setText("Sample stopped at target value"); }
          else if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 5) { rotStatus_->setText("Sample moving toward set point"); }
          else if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 6) { rotStatus_->setText("Reserved"); }
          else if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 7) { rotStatus_->setText("Reserved"); }
          else if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 8) { rotStatus_->setText("Sample hit limit switch"); }
          else if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 9) { rotStatus_->setText("Sample hit index switch"); }
          else if (((static_cast<int>(ppmsStatus) >> 12) & 0b1111) == 15) { rotStatus_->setText("General failure "); }
          else { rotStatus_->setText("Reserved"); }

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
    sampleSpacePressure_ = new QLabel();
    sampleSpacePressure_->setText("");

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
    auto labelSampleSpacePressure = new QLabel ("Chamber Pressure: ");

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
    ChamberGridLayout->addWidget(labelChamberStatus, 2, 0);
    ChamberGridLayout->addWidget(chamberStatus_ , 2, 1);
    ChamberGridLayout->addWidget(labelSampleSpacePressure, 1, 0);
    ChamberGridLayout->addWidget(sampleSpacePressure_, 1, 1);
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

