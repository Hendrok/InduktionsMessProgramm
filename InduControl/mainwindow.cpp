#include <QtWidgets>

#include "mainwindow.h"
#include "../InduControlCore/indumanager.h"
#include "../InduCore/measurementsequence.h"
#include "graphdiagram.h"
#include "../InduCore/datapoint.h"
#include "startdialog.h"
#include <memory>
#include "../InduControlCore/ppmssimulation.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , graph_(new GraphDiagram(this))
    , indumanager_(new InduManager())

{    
    createStatusBar();
    createActions();
    createQLineDiagramm();

    setCentralWidget(graph_);
}

MainWindow::~MainWindow()
{
    delete indumanager_;
}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&Measurement"));
    QToolBar *fileToolBar = addToolBar(tr("New Measurement"));
    const QIcon measurementIcon =QIcon::fromTheme("MessungIcon", QIcon(":/Icons/Icons/StartButton.png"));
    QAction *messungStarten = new QAction(measurementIcon, tr("&New Measurement"), this);
    messungStarten->setStatusTip(tr("Create a new measurement"));
    connect(messungStarten, &QAction::triggered, this, &MainWindow::onStartMessungButton); //Hier sende ich Signal ans Slot
    fileMenu->addAction(messungStarten);
    fileToolBar->addAction(messungStarten);


}
void MainWindow::onStartMessungButton()
{
    StartDialog* startDialog = new StartDialog(this);
    connect(startDialog, &StartDialog::startMeasurement,
            this, &MainWindow::onStartMeasurement);
    startDialog->show();
}

void MainWindow::onStartMeasurement(std::shared_ptr<const MeasurementSequence> mSeq)
{
    indumanager_->startMeasurement(mSeq);
    connect(indumanager_,&InduManager::newData,
            this,&MainWindow::onNewData);
    graph_->setStaticValues(mSeq);
}

void MainWindow::onNewData(std::shared_ptr<const DataPoint> datapoint)
{
    graph_->appendDataPoint(datapoint);
}

void MainWindow::createQLineDiagramm()
{
    graph_->createQlineDiagramm();
}
void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}


