#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "../InduCore/measurementsequence.h"
#include "../InduCore/MeasSeqTc.h"
#include "../InduControlCore/indumanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<InduManager> indumanager_;

};
#endif // MAINWINDOW_H
