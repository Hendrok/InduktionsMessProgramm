#ifndef GRAPHDIAGRAM_H
#define GRAPHDIAGRAM_H

//includes std
#include <memory>
//includes qt
#include <QWidget>
#include <QtCharts>
#include <QtCharts/QValueAxis>
class DataPoint;
class MeasurementSequence;

class GraphDiagram: public QWidget
{
    Q_OBJECT
public:

    GraphDiagram(QWidget*parent =nullptr);
    void createQlineDiagramm();
    void appendDataPoint(std::shared_ptr<const DataPoint> datapoint);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    QVector<double> temps_;
    QVector<double> volts_;
    QString filename1_;
    double tempmin_;
    double tempmax_;
    double voltmin_;
    double voltmax_;
    double phase_;
    QLineSeries *series_;
    QChart *chart_;
    QChartView *chartView_;
    QValueAxis *axisX_ ;
    QValueAxis *axisY_;
public slots:
    void setAxis(std::shared_ptr<const MeasurementSequence> mSeq);
};

#endif // GRAPHDIAGRAM_H
