#include <QtWidgets>
#include <memory>

//Internal Classes
#include "mainwindow.h"
#include "../InduControlCore/indumanager.h"
#include "../InduCore/measurementsequence.h"
#include "graphdiagram.h"
#include "../InduCore/datapoint.h"
#include "startdialog.h"
#include "../Instruments/ppmssimulation.h"
#include "ppmswidget.h"
#include "measurementstable.h"
#include "QDialog"

#include "../Instruments/ppmsinstrument.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , graph_(new GraphDiagram(this))
    , indumanager_(new InduManager())
    , indumanagerState_(InduManager::State::Idle)
    , ppmsWidget_(new PpmsWidget())
    , mainLayoutWidget(new QWidget())
    , mTable(new MeasurementsTable())
{    
    setupUi();
    createStatusBar();
    createActions();
    createQLineDiagramm();
    setCentralWidget(mainLayoutWidget);

    connect(indumanager_, &InduManager::startNewMeasurement,
            this, &MainWindow::onStartMeasurement);
    connect(indumanager_,&InduManager::newData,
            this,&MainWindow::onNewData);
    connect(indumanager_, &InduManager::newState,
            this, &MainWindow::onNewMeasurementState);
    connect(indumanager_, &InduManager::newTempSP,
            this, &MainWindow::onNewTempSP);
    connect(indumanager_, &InduManager::newMagSP,
            this, &MainWindow::onNewMagSP);
    connect(indumanager_, &InduManager::newAngleSP,
            this, &MainWindow::onNewAngleSP);
    connect(indumanager_, &InduManager::newErrorMessagePpms,
            this, &MainWindow::onNewErrorMessagePpms);
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

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Quit?",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

void MainWindow::setupUi()
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* GraphandList = new QHBoxLayout();
    GraphandList->addWidget(graph_);
    GraphandList->addWidget(mTable);
    mTable->setMaximumWidth(250);
    mainLayout->addLayout(GraphandList);
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
    connect(messungStarten, &QAction::triggered,
            this, &MainWindow::onStartMessungButton);
    fileMenu->addAction(messungStarten);
    fileToolBar->addAction(messungStarten);
}

void MainWindow::onStartMessungButton()
{

    StartDialog* startDialog = new StartDialog(this);
    connect(startDialog, &StartDialog::createMeasurement,
            this, &MainWindow::onCreateMeasurement);
    startDialog->show();

}

void MainWindow::onCreateMeasurement(std::vector<std::shared_ptr<const MeasurementSequence> > mSeq)
{ 
    indumanager_->appendMeasurement(mSeq);
    mTable->newMeasurement(mSeq);
}

void MainWindow::onStartMeasurement(std::shared_ptr<const MeasurementSequence> mSeq)
{    
    graph_->setStaticValues(mSeq);
    mTable->activeMeasurement(mSeq);
}

void MainWindow::onNewData(std::shared_ptr<const DataPoint> datapoint)
{
    ppmsWidget_->newData(datapoint);
    graph_->appendDataPoint(datapoint);
}

void MainWindow::onNewMeasurementState(InduManager::State newState)
{
    indumanagerState_ = newState;
    graph_->MeasurementState(indumanagerState_);
}

void MainWindow::onNewTempSP(double temp, double rate)
{
    ppmsWidget_->newTempSP(temp,rate);
}

void MainWindow::onNewMagSP(double magField, double magRate)
{
    ppmsWidget_->newMagSP(magField, magRate);
}

void MainWindow::onNewAngleSP(double angle)
{
    ppmsWidget_->newAngleSP(angle);
}

void MainWindow::onNewErrorMessagePpms(QString errormessagePpms)
{
    qDebug()<<"hi";
    QMessageBox* msgBox = new QMessageBox( this );
       msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
       msgBox->setStandardButtons( QMessageBox::Ok );
       msgBox->setWindowTitle( tr("Error") );
       msgBox->setText(errormessagePpms);
       msgBox->setModal( false ); // if you want it non-modal
       msgBox->open( this, SLOT(msgBoxClosed(QAbstractButton*)) );
}

void MainWindow::createQLineDiagramm()
{
    graph_->createQlineDiagramm();
}
void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}


