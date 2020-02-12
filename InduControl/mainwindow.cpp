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
    QMenu *fileMenu = menuBar()->addMenu(tr("&Messungen"));
    QToolBar *fileToolBar = addToolBar(tr("Messungen"));
    QAction *newAct = new QAction( tr("&Neue Messung"), this);
    newAct->setStatusTip(tr("Create a new measurement"));
    connect(newAct, &QAction::triggered, this, &MainWindow::onStartMessungButton);
    //connect(newAct, &QAction::triggered, this, &MainWindow::createQLineDiagramm);
    fileMenu->addAction(newAct);
    fileToolBar->addAction(newAct);
}
void MainWindow::onStartMessungButton() // damit ich werte nacher eingeben kann muss hier measurementsequ. initialisiert werden
{
    StartDialog* startDialog = new StartDialog(this);
    connect(startDialog, &StartDialog::startMeasurement,
            this, &MainWindow::onStartMeasurement);

    startDialog->show();

}

void MainWindow::onStartMeasurement(std::shared_ptr<const MeasurementSequence> mSeq)
{
    indumanager_->startMeasurement(mSeq);
}

void MainWindow::createQLineDiagramm()
{
    graph_->appendDataPoint(std::make_shared<const DataPoint>());
    graph_->createQlineDiagramm();

}
void MainWindow::createStatusBar()
//! [32] //! [33]
{
    statusBar()->showMessage(tr("Ready"));
}


