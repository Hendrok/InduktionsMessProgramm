#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <vector>
#include <QMainWindow>
#include <QCloseEvent>
#include <QCheckBox>
#include "../InduControlCore/indumanager.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QPlainTextEdit;
class QSessionManager;
class MeasSeqTc;
class MeasurementSequence;
class DataPoint;
class GraphDiagram;
class PpmsSimulation;
class PpmsWidget;
class MeasurementsTable;

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void closeEvent (QCloseEvent *event) override;

private slots:
    void onStartMessungButton();
    void onCreateMeasurement(std::vector<std::shared_ptr<const MeasurementSequence>> mSeq);
    void onStartMeasurement(std::shared_ptr<const MeasurementSequence> mSeq);
    void onSetSampleStage(bool rotator);
    void onNewData(std::shared_ptr<const DataPoint> datapoint);
    void onNewMeasurementState(InduManager::State newState);
    void onNewTempSP(double temp, double rate);
    void onNewMagSP(double magField, double magRate);
    void onNewAngleSP(double angle);
    void onNewErrorMessage(QString errormessagePpms);
private:
    void setupUi();
    void createStatusBar();
    void createActions();
    void createQLineDiagramm();
    void createRotatorButton();

    GraphDiagram *graph_;
    InduManager* indumanager_;
    InduManager::State indumanagerState_;
    PpmsWidget* ppmsWidget_;
    QWidget* mainLayoutWidget;
    MeasurementsTable* mTable;
    QCheckBox *rotCheckBox_;
};
#endif // MAINWINDOW_H
