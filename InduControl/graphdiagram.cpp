#include "graphdiagram.h"

#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <memory>
#include <QDebug>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QVBoxLayout>

// eigene Sachen
#include "../InduCore/datapoint.h"
#include "../InduCore/measurementsequence.h"
#include "../InduCore/measseqtc.h"
#include "../InduControlCore/indumanager.h"
QT_CHARTS_USE_NAMESPACE


GraphDiagram::GraphDiagram(QWidget *parent)
    :QWidget(parent)
    , filename1_("filename")
    , tempmin_(0)
    , tempmax_(100)
    , voltmin_(0)
    , voltmax_(0)
    , phase_(0)
    , graphMeas_(false)
    , series_(new QLineSeries())
    , chart_(new QChart())
    , chartView_(new QChartView(chart_))
    , axisX_(new QValueAxis)
    , axisY_(new QValueAxis)

{

}


void GraphDiagram::appendDataPoint(std::shared_ptr<const DataPoint> datapoint)
{
    //für die Range
    if(voltmin_==0){voltmin_=datapoint->lockindata()->pvVoltLive();}
    if(voltmin_>datapoint->lockindata()->pvVoltLive()){voltmin_=datapoint->lockindata()->pvVoltLive()-0.1;}
    //if(voltmin_<0){voltmin_=0;}
    if(voltmax_<datapoint->lockindata()->pvVoltLive()){voltmax_=datapoint->lockindata()->pvVoltLive()+0.1;}


    series_->append(datapoint->ppmsdata()->pvTempLive(), datapoint->lockindata()->pvVoltLive());

    // set Range Live
    axisY_->setRange(voltmin_,voltmax_);

}

QSize GraphDiagram::sizeHint() const
{
    return QSize(700, 500);
}

QSize GraphDiagram::minimumSizeHint() const
{
    return QSize(300, 200);
}

void GraphDiagram::setStaticValues(std::shared_ptr<const MeasurementSequence> mSeq)
{
    series_->clear();
    auto seqTc = std::dynamic_pointer_cast <const MeasSeqTc> (mSeq);
    if(seqTc !=nullptr)
        {
        if(seqTc->tempStart() <= seqTc->tempEnd())
        {
            axisX_->setRange(seqTc->tempStart(),seqTc->tempEnd());
        }
        else
        {
            axisX_->setRange(seqTc->tempEnd(),seqTc->tempStart());
        }

        QString title= mSeq->fileName();
        chart_->setTitle("Tc Measurement " + mSeq->fileName());
    }
}

void GraphDiagram::createQlineDiagramm()
{
   chart_->legend()->hide();
   chart_->addSeries(series_);

   axisX_->setTitleText("Temperature in Kelvin");


   axisY_->setTitleText("Voltage in Volt");
   chart_->addAxis(axisX_, Qt::AlignBottom);
   chart_->addAxis(axisY_, Qt::AlignLeft);
   series_->attachAxis(axisX_);
   series_->attachAxis(axisY_);

   //font Size
   QFont font;
   font.setPixelSize(18);
   chart_->setTitleFont(font);



   // Dicke der Linie
   QPen pen(QRgb(0x000000));
   pen.setWidth(2);
   series_->setPen(pen);
   // Animationen alle an, weil Animationen cool
   chart_->setAnimationOptions(QChart::NoAnimation);

   //Durch Antialiasing passt sich chart an, wenn man größer kleiner macht (meine ich)
   //QChartView *chartView = new QChartView(chart_);
   chartView_->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(chartView_);

    setLayout(mainLayout);
}




