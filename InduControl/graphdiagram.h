#ifndef GRAPHDIAGRAM_H
#define GRAPHDIAGRAM_H

//includes std
#include <memory>
//includes qt
#include <QWidget>
class DataPoint;

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
};

#endif // GRAPHDIAGRAM_H
