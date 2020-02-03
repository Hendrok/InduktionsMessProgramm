#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../InduCore/measurementsequence.h"
#include "QString"
#include <memory>
#include "../InduCore/filewriter.h"
#include "classtestmanager.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)


{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//TODO: meine ui klappt nicht, bzw die werte aus der Ui den attributen hinzuzufügen
void MainWindow::on_pushButton_clicked()
{
    measurementSequence  = std::make_shared<MeasurementSequence>();
    QString SupraName;
    double StartTemp =ui->StartTemp->value();
    double EndTemp=ui->EndTemp->value();
    double temperatureRate =ui->TempRate->value();
    double magneticField =ui->MagField->value();
    double coilAngle=ui->CoilAngle->value();
    //Lockin
    double frequency =ui->Frequency->value();
    double voltageAmplitude= ui->VoltageAmplitude->value();
    int harmonicWave=ui->HarmonicWave->value();

    SupraName.append(ui->SupraName1->text());
    measurementSequence->setSupraName(SupraName);
    measurementSequence->setTempStart(StartTemp);
    measurementSequence->setTempEnd(EndTemp);
    measurementSequence->setTemperatureRate(temperatureRate);
    measurementSequence->setMagneticField(magneticField);
    measurementSequence->setCoilAngle(coilAngle);
    measurementSequence->setFrequency(frequency);
    measurementSequence->setVoltageAmplitude(voltageAmplitude);
    measurementSequence->setHarmonicWave(harmonicWave);

    ClassTestManager ctm;
    ctm.startMeasurement(measurementSequence);

}

