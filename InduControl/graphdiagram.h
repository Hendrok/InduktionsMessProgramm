#ifndef GRAPHDIAGRAM_H
#define GRAPHDIAGRAM_H

//includes std
#include <memory>
//includes qt
#include <QWidget>
class DataPoint;

class graphDiagram
{
public:
    graphDiagram();
    void createQlineDiagramm();
    void createDataPoint(std::shared_ptr<DataPoint> datapoint);
private:
    QVector<double> temps_;
    QVector<double> volts_;
    QString filename1_;
};

#endif // GRAPHDIAGRAM_H
