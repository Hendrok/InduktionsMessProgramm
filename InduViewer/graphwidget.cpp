#include "graphwidget.h"
#include "../InduCore/filereader.h"

#include <QString>
#include <QTextStream>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <memory>
#include <QDebug>
QT_CHARTS_USE_NAMESPACE
using namespace std;

GraphWidget::GraphWidget(Datafile &cfile)
    :cfile_(cfile)
{

}

void GraphWidget::createDatapoints(std::shared_ptr<Datafile> datafile){
    volts_=datafile->getVoltage();
    temps_=datafile->getTemperature();
    filename1_=cfile_.getFileName();   //cfile. pointet auf getfilename
    //qDebug()<<filename1_;

}


void GraphWidget::createQlineDiagramm(){



    QVector <double> TemperaturVektordouble =temps_;
    QVector<double> VoltageVektordouble= volts_;


   QString filename_2 ="TCMessung: ";

   // Für Später, hier soll der name Geändert werden, da die Datei Momentan am Ende noch mit.txt angezeigt wird, checke aber nicht genau wie QDir mit filename funktioniert
   //QDir themeDir =QFileInfo(filename).dir();
   //QString themeName= themeDir.dirName();

   //dadurch ist die Überschrfrift z.b: TCMessung: Ybco_48_Trölfzen.txt

   QString filename=filename1_;
   //qDebug()<<filename;
   QString filename_3 = filename.section('/',-1);
   filename_2.append(filename_3);

   //erstelle das LinienDiagramm
   QLineSeries *series =new QLineSeries();
   // for schleife schmeißt daten in Diagramm
   for(int j=0;j<TemperaturVektordouble.length()-2;j++)
   {
   series->append(TemperaturVektordouble[j],VoltageVektordouble[j]);
   }

   //chart des Diagramms
   QChart *chart =new QChart();
   chart->legend()->hide();
   chart->addSeries(series);
   //chart->createDefaultAxes();
   //X-Achse plus Beschreibung
   QValueAxis *axisX = new QValueAxis;
   axisX->setTitleText("Temperatur in Kelvin");
   //Y-Achse plus Beschreibung
   QValueAxis *axisY= new QValueAxis;
   axisY->setTitleText("Spannung in Volt");
   chart->addAxis(axisX, Qt::AlignBottom);
   chart->addAxis(axisY, Qt::AlignLeft);
   series->attachAxis(axisX);
   series->attachAxis(axisY);

   //font Size
   QFont font;
   font.setPixelSize(18);
   chart->setTitleFont(font);
   // Titel von oben einsetzen
   chart->setTitle(filename_2);

   // Dicke der Linie
   QPen pen(QRgb(0x000000));
   pen.setWidth(2);
   series->setPen(pen);
   // Animationen alle an, weil Animationen cool
   chart->setAnimationOptions(QChart::AllAnimations);

   //Durch Antialiasing passt sich chart an, wenn man größer kleiner macht (meine ich)
   QChartView *chartView = new QChartView(chart);
   chartView->setRenderHint(QPainter::Antialiasing);
   // ich meine das dieser Befehl, die Chart im neuen Fenster öffnet, was danach noch auf die richtige Größe gesetzt wird
   chartView->show();
   chartView->resize(1000,800);

}
