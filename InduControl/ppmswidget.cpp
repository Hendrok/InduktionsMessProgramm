#include "ppmswidget.h"

#include <QDebug>

#include "../InduCore/datapoint.h"

PpmsWidget::PpmsWidget(QWidget *parent)
    : QWidget (parent)
{
    
}

QSize PpmsWidget::sizeHint() const
{
    return QSize(150,300);   
}

QSize PpmsWidget::minimumSizeHint() const
{
    return QSize(100,200);   
}

void PpmsWidget::newData(std::shared_ptr<const DataPoint> dpoint)
{
    if(dpoint != nullptr){
        // label auf Heliumlevel?
    }
    
}

