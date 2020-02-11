#include <QtWidgets>

#include "mainwindow.h"
#include "../InduControlCore/indumanager.h"
#include "../InduCore/measurementsequence.h"
#include "graphdiagram.h"
#include "../InduCore/datapoint.h"
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , datapoint_(std::shared_ptr<DataPoint>())
    , textEdit(new QPlainTextEdit)

{
    setCentralWidget(textEdit);
    createStatusBar();
    createActions();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&Messungen"));
    QToolBar *fileToolBar = addToolBar(tr("Messungen"));
    QAction *newAct = new QAction( tr("&Neue Messung"), this);
    newAct->setStatusTip(tr("Create a new measurement"));
    connect(newAct, &QAction::triggered, this, &MainWindow::StartMessung);
    connect(newAct, &QAction::triggered, this, &MainWindow::creatQLineDiagramm);
    fileMenu->addAction(newAct);
    fileToolBar->addAction(newAct);
}
void MainWindow::StartMessung(/*std::shared_ptr<MeasurementSequence> measurementSequence*/)
{
    InduManager *indumanager_= new InduManager;
    measurementSequence_=std::make_shared <MeasurementSequence>();
    indumanager_->startMeasurement(measurementSequence_);
}
void MainWindow::creatQLineDiagramm() // wie kann ich connecten und gleichzeitig datapoints initialisieren?
{
    graphDiagram *gD=new graphDiagram;
    gD->createDataPoint(datapoint_);
    gD->createQlineDiagramm();
}
void MainWindow::createStatusBar()
//! [32] //! [33]
{
    statusBar()->showMessage(tr("Ready"));
}


