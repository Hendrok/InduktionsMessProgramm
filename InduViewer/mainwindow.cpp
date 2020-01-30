#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../InduCore/filereader.h"
#include "graphwidget.h"

#include <QString>
#include <QFileDialog>
#include <memory>
#include <QDebug>

using namespace std;

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


void MainWindow::on_TextSuche_clicked()
{

    //Öffne die MessDatei
    QFile file(QFileDialog::getOpenFileName(this,
                                                  tr("OPEN FILE"),
                                                  "C:",
                                                  tr("All files(*.*);;Text File(*.txt)")));

    file.open(QIODevice::ReadOnly |QIODevice::Text);
    // die Textdatei wird komplett eingelesen
    QTextStream stream(&file);
    QString text=stream.readAll();

    //sette input text
    datafile->setInputText(text);
    FileReader fReader(*datafile);  //erstelle classe FileReader und rufe constructor auf
    fReader.readFile();             //rufe readfile auf
    datafile=fReader.readFile();    //setze datafile= return von readfile




    //Label wird mit Filenamen besetzt.
    filename=file.fileName();
    ui->label->setText(filename);






}


void MainWindow::on_DialogOpen_clicked()
{
    datafile->setFileName(filename);
    GraphWidget gGraph(*datafile);

    gGraph.createDatapoints(datafile);
    gGraph.createQlineDiagramm();



}




