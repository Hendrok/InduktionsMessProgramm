#include <QtWidgets>
#include <memory>

#include "mainwindow.h"
#include "../InduControlCore/indumanager.h"
#include "../InduCore/measurementsequence.h"
#include "graphdiagram.h"
#include "../InduCore/datapoint.h"
#include "startdialog.h"
#include "../InduControlCore/ppmssimulation.h"
#include "ppmswidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , graph_(new GraphDiagram(this))
    , indumanager_(new InduManager())
    , ppmsWidget_(new PpmsWidget())
    , mainLayoutWidget(new QWidget())

{    
    setupUi();
    createStatusBar();
    createActions();
    createQLineDiagramm();
    setCentralWidget(mainLayoutWidget);
}

MainWindow::~MainWindow()
{
    delete indumanager_;
}


QSize MainWindow::sizeHint() const
{
    return QSize(1600, 800);
}

QSize MainWindow::minimumSizeHint() const
{
    return QSize(800, 400);

}

void MainWindow::setupUi()
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(graph_);
    mainLayout->addSpacing(10);
    ppmsWidget_->setMaximumHeight(120);
    mainLayout->addWidget(ppmsWidget_);
    mainLayoutWidget->setLayout(mainLayout);
}


void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&Measurement"));
    QToolBar *fileToolBar = addToolBar(tr("New Measurement"));
    const QIcon measurementIcon =QIcon::fromTheme("MessungIcon", QIcon(":/Icons/Icons/Tc.svg"));
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
    if(indumanager_->getMeasurementState()==InduManager::State::Idle)
    {
    indumanager_->startMeasurement(mSeq);
    connect(indumanager_,&InduManager::newData,
            this,&MainWindow::onNewData);
    graph_->setStaticValues(mSeq);
    }
}

void MainWindow::onNewData(std::shared_ptr<const DataPoint> datapoint)
{
    ppmsWidget_->newData(datapoint);
    if(indumanager_->getMeasurementState()==InduManager::State::ApproachEnd)
    {
    graph_->appendDataPoint(datapoint);
    }




}

void MainWindow::createQLineDiagramm()
{
    graph_->createQlineDiagramm();
}
void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}


