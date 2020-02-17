#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<memory>

#include <QMainWindow>
QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QPlainTextEdit;
class QSessionManager;
class InduManager;
class MeasSeqTc;
class MeasurementSequence;
class DataPoint;
class GraphDiagram;
class PpmsSimulation;
class PpmsWidget;

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private slots:
    void onStartMessungButton();
    void onStartMeasurement(std::shared_ptr<const MeasurementSequence> mSeq);
    void onNewData(std::shared_ptr<const DataPoint> datapoint);


private:
    void createStatusBar();
    void createActions();
    void createQLineDiagramm();

    GraphDiagram *graph_;
    InduManager* indumanager_;
    PpmsWidget* ppmsWidget_;

};
#endif // MAINWINDOW_H
