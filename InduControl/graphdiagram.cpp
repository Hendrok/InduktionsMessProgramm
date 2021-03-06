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

//Internal Classes
#include "../InduCore/datapoint.h"
#include "../InduCore/measurementsequence.h"
#include "../InduCore/measseqtc.h"
#include "../InduCore/measseqjc.h"
#include "../InduControlCore/indumanager.h"
QT_CHARTS_USE_NAMESPACE


GraphDiagram::GraphDiagram(QWidget *parent)
    :QWidget(parent)
    , filename1_("filename")
    , tempmin_(0)
    , tempmax_(100)
    , voltmin_(10)
    , voltmax_(10)
    , phase_(0)
    , graphMeas_(false)
    , series_(new QLineSeries())
    , chart_(new QChart())
    , chartView_(new QChartView(chart_))
    , axisX_(new QValueAxis)
    , axisY_(new QValueAxis)
    , measSeq_ (nullptr)
    , measurementState_(InduManager::State::Idle)
{

}


void GraphDiagram::appendDataPoint(std::shared_ptr<const DataPoint> datapoint)
{
    if(measurementState_ == InduManager::State::ApproachEndTc)
    {
    // Range of Y-Axis
    if(voltmin_ == 10) {voltmin_ = datapoint->lockindata()->pvVoltOutputLive();}
    if(voltmax_ == 10) {voltmax_ = datapoint->lockindata()->pvVoltOutputLive();}
    //if(voltmin_<=0){voltmin_=datapoint->lockindata()->pvVoltOutputLive();}
    if(voltmin_>datapoint->lockindata()->pvVoltOutputLive()){voltmin_=datapoint->lockindata()->pvVoltOutputLive()-0.00001;}
    if(voltmax_<datapoint->lockindata()->pvVoltOutputLive()){voltmax_=datapoint->lockindata()->pvVoltOutputLive()+0.00001;}
    axisY_->setRange(voltmin_,voltmax_);

    series_->append(datapoint->ppmsdata()->pvTempLive(), datapoint->lockindata()->pvVoltOutputLive());

    }

    else if(measurementState_ == InduManager::State::ApproachEndJc)
    {
    // Range of Y-Axis
    if(voltmin_ == 10) {voltmin_ = datapoint->lockindata()->pvVoltOutputLive();}
    if(voltmax_ == 10) {voltmax_ = datapoint->lockindata()->pvVoltOutputLive();}
    //if(voltmin_ <= 0){voltmin_=datapoint->lockindata()->pvVoltOutputLive();}
    if(voltmin_>datapoint->lockindata()->pvVoltOutputLive()){voltmin_=datapoint->lockindata()->pvVoltOutputLive()-0.01;}
    if(voltmax_<datapoint->lockindata()->pvVoltOutputLive()){voltmax_=datapoint->lockindata()->pvVoltOutputLive()+0.01;}
    axisY_->setRange(voltmin_,voltmax_);

    series_->append(datapoint->lockindata()->pvVoltInputLive(), datapoint->lockindata()->pvVoltOutputLive());

    }
}

void GraphDiagram::MeasurementState(InduManager::State newState)
{
 measurementState_ = newState;
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
    measSeq_ = mSeq;
    auto mSeqTc = std::dynamic_pointer_cast <const MeasSeqTc> (measSeq_);
    auto mSeqJc = std::dynamic_pointer_cast <const MeasSeqJc> (measSeq_);
    if(mSeqTc !=nullptr)
    {
        axisX_->setTitleText("Temperature in Kelvin");
        axisY_->setTitleText("Voltage in Volt");

        if(mSeqTc->tempStart() <= mSeqTc->tempEnd())
        {
            axisX_->setRange(mSeqTc->tempStart(),mSeqTc->tempEnd());
        }
        else
        {
            axisX_->setRange(mSeqTc->tempEnd(),mSeqTc->tempStart());
        }

        QString title= mSeq->fileName();
        chart_->setTitle("Tc Measurement " + mSeq->fileName());
    }
    else if(mSeqJc !=nullptr)
    {
        axisX_->setTitleText("Input Voltage in Volt");
        axisY_->setTitleText("Output Voltage in Volt");
        if(mSeqJc->voltStart() <= mSeqJc->voltEnd())
        {
            axisX_->setRange(mSeqJc->voltStart(), mSeqJc->voltEnd());
        }
        else
        {
            axisX_->setRange(mSeqJc->voltEnd(), mSeqJc->voltStart());
        }

        QString title= mSeq->fileName();
        chart_->setTitle("Jc Measurement " + mSeq->fileName());
    }


}

void GraphDiagram::createQlineDiagramm()
{
    chart_->legend()->hide();
    chart_->addSeries(series_);
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




