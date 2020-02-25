#ifndef GRAPHDIAGRAM_H
#define GRAPHDIAGRAM_H

#include <memory>
#include <QWidget>
#include <QtCharts>
#include <QtCharts/QValueAxis>

//Internal Classes
class DataPoint;
class MeasurementSequence;
class measSeqJc;
class measSeqTc;
class InduManager;

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
    bool graphMeas_;
    QLineSeries *series_;
    QChart *chart_;
    QChartView *chartView_;
    QValueAxis *axisX_ ;
    QValueAxis *axisY_;

    std::shared_ptr <const MeasurementSequence> measSeq_;
    int measurementType; /*TODO
                          * Either Implement measSeq_tc and jc in private, or implement measurementType as a state?
                          */
public slots:
    void setStaticValues(std::shared_ptr<const MeasurementSequence> mSeq);

};

#endif // GRAPHDIAGRAM_H
