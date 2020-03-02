#include "measurementstable.h"
#include <QVBoxLayout>
#include <QDebug>

#include "../InduCore/measurementsequence.h"

MeasurementsTable::MeasurementsTable(QWidget *parent)
    : QWidget (parent)
    , listWidget(new QListWidget(this))
{
    SetupUI();
}

QSize MeasurementsTable::sizeHint() const
{
    return QSize(200,500);
}

QSize MeasurementsTable::minimumSizeHint() const
{
    return QSize(100,300);
}

void MeasurementsTable::newMeasurement(std::vector<std::shared_ptr<const MeasurementSequence> > mSeq)
{
    vecSeq_=mSeq;
    for (unsigned long i=0; i<mSeq.size();i++)
    {
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(mSeq[i]->fileName());
        listWidget->addItem(item);
        /*TODO:
         * for Schleife ändern->
         *new QListWidgetItem(tr(QString::to(Element->fileName())), listWidget);
        */
    }
}

void MeasurementsTable::activeMeasurement(std::shared_ptr<const MeasurementSequence> mesSeq)
{
        auto element(mesSeq);
        auto it = std::find(vecSeq_.begin(), vecSeq_.end(), element);
        if(it != vecSeq_.end())
        {
            listWidget->item(it - vecSeq_.begin())->setForeground(Qt::red);
        }
        else
        {
            listWidget->item(it - vecSeq_.begin())->setForeground(Qt::black);
        }



}

void MeasurementsTable::SetupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(listWidget);
    setLayout(mainLayout);
}
