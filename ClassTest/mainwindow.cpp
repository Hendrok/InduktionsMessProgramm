#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../InduCore/measurementsequence.h"
#include "QString"
#include <memory>
#include "../InduCore/filewriter.h"
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
    QString SupraName= "hi";
    double StartTemp =10;//ui->StartTemp->value();
    double EndTemp=10;//ui->EndTemp->value();
    double temperatureRate =10;//ui->TempRate->value();
    double magneticField =10;//ui->MagField->value();
    double coilAngle=10;//ui->CoilAngle->value();
    //Lockin
    double frequency =10;//ui->Frequency->value();
    double voltageAmplitude=10;// ui->VoltageAmplitude->value();
    int harmonicWave=10;//ui->HarmonicWave->value();

    //SupraName.append(ui->SupraName1->toPlainText());
    measurementSequence->setSupraName(SupraName);
    measurementSequence->setTempStart(StartTemp);
    measurementSequence->setTempEnd(EndTemp);
    measurementSequence->setTemperatureRate(temperatureRate);
    measurementSequence->setMagneticField(magneticField);
    measurementSequence->setCoilAngle(coilAngle);
    measurementSequence->setFrequency(frequency);
    measurementSequence->setVoltageAmplitude(voltageAmplitude);
    measurementSequence->setHarmonicWave(harmonicWave);

    FileWriter fw(measurementSequence);
    QString header =fw.writeHeader(measurementSequence);
    qDebug()<<header;
}

