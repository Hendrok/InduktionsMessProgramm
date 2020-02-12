#include "graphdiagram.h"
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
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtDebug>
#include <QtWidgets/QVBoxLayout>
//includes std
#include <algorithm>
#include "../InduCore/datapoint.h"
QT_CHARTS_USE_NAMESPACE



GraphDiagram::GraphDiagram(QWidget *parent)
    :QWidget(parent)
    , filename1_("filename")
    , temp_(0)
    , volt_(0)
    , phase_(0)

{

}

void GraphDiagram::appendDataPoint(std::shared_ptr<const DataPoint> datapoint)
{
    temp_ =datapoint->pvTemp();
    volt_ =datapoint->pvVolt();
    phase_ = datapoint->pvPhase();

}

QSize GraphDiagram::sizeHint() const
{
    return QSize(700, 500);
}

QSize GraphDiagram::minimumSizeHint() const
{
    return QSize(300, 200);
}

void GraphDiagram::createQlineDiagramm()
{

    QVector <double> TemperaturVektordouble =temps_;
    QVector<double> VoltageVektordouble= volts_;


   QString filename_2 ="TCMessung: ";

   QString filename=filename1_;
   //qDebug()<<filename;
   QString filename_3 = filename.section('/',-1);
   filename_2.append(filename_3);

   //erstelle das LinienDiagramm
   QLineSeries *series =new QLineSeries();

   series->append(temp_,volt_);

   //chart des Diagramms
   QChart *chart = new QChart();
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

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(chartView);

    setLayout(mainLayout);
}


