#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H
#include "../InduCore/datafile.h"

//includes std
#include <memory>
//includes qt
#include <QWidget>



class GraphWidget
{
public:
    GraphWidget(Datafile &cfile);
    void createQlineDiagramm();
    void createDatapoints(std::shared_ptr<Datafile> datafile);
private:
    Datafile cfile_;

    QVector<double> temps_;
    QVector<double> volts_;
    QString filename1_;
    //std::shared_ptr<Datafile> datafile = std::make_shared<Datafile>();
};

#endif // GRAPHWIDGET_H
