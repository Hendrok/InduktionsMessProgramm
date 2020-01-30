#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../InduCore/datafile.h"

#include<string>
#include <QMainWindow>
#include <memory>

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


    void on_TextSuche_clicked();

    void on_DialogOpen_clicked();



private:
    Ui::MainWindow *ui;

    QString filename;
    std::shared_ptr<Datafile> datafile = std::make_shared<Datafile>();
};
#endif // MAINWINDOW_H
