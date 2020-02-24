#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <memory>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <memory>

//Eigene Klassen

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
/*
//TODO: meine ui klappt nicht, bzw die werte aus der Ui den attributen hinzuzufügen
void MainWindow::on_pushButton_clicked()
{
    //die per Ui eingetragenen Attribute werden erstellt
    MeasSeqTc measurementSequence;


    QString SupraName;
    double StartTemp =ui->StartTemp->value();
    double EndTemp=ui->EndTemp->value();
    double temperatureRate =ui->TempRate->value();
    double magneticField =ui->MagField->value();
    double coilAngle=ui->CoilAngle->value();
    double frequency =ui->Frequency->value();
    double voltageAmplitude= ui->VoltageAmplitude->value();
    int harmonicWave=ui->HarmonicWave->value();

    // die eingegeben Attribute werden in measurementSequence "gesettet"
    SupraName.append(ui->SupraName1->text());
    measurementSequence.setSupraName(SupraName);
    measurementSequence.setTempStart(StartTemp);
    measurementSequence.setTempEnd(EndTemp);
    measurementSequence.setTemperatureRate(temperatureRate);
    measurementSequence.setMagneticField(magneticField);
    measurementSequence.setCoilAngle(coilAngle);
    measurementSequence.setFrequency(frequency);
    measurementSequence.setVoltageAmplitude(voltageAmplitude);
    measurementSequence.setHarmonicWave(harmonicWave);

    auto ptr = std::make_shared<const MeasSeqTc>(measurementSequence);

    InduManager *idm = new InduManager;
    //idm->startMeasurement(ptr);
}

*/
