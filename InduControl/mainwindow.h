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
class MeasurementSequence;
class DataPoint;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
     void StartMessung(/*std::shared_ptr<MeasurementSequence> measurementSequence*/);
private:
    std::shared_ptr<DataPoint> datapoint_;
    void createStatusBar();
    void createActions();
    void creatQLineDiagramm();
    QPlainTextEdit *textEdit;
    std::unique_ptr<InduManager> indumanager_;
    std::shared_ptr<MeasurementSequence> measurementSequence_;
};
#endif // MAINWINDOW_H
