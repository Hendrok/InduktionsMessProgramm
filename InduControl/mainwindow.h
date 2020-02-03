#ifndef MAINWINDOW_H                          //Aufgabe:QWidget Application(UI des Programms)User Interface von Messen
#define MAINWINDOW_H                          //MainWindow-> erstellt MainWindow beim öffnen
                                              //Widget mit dem man PPMS zeugs anzeigen kann
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
