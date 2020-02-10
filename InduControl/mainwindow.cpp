#include <QtWidgets>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , textEdit(new QPlainTextEdit)
{
    setCentralWidget(textEdit);
    createStatusBar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{

}
void MainWindow::createStatusBar()
//! [32] //! [33]
{
    statusBar()->showMessage(tr("Ready"));
}


