#include "measurementstable.h"
#include <QVBoxLayout>
#include <QDebug>

#include "../InduCore/measurementsequence.h"

MeasurementsTable::MeasurementsTable(QWidget *parent)
    : QWidget (parent)
    , listWidget(new QListWidget(this))
    , vecSeq_()
{
    setupUI();
}

QSize MeasurementsTable::sizeHint() const
{
    return QSize(200,500);
}

QSize MeasurementsTable::minimumSizeHint() const
{
    return QSize(100,300);
}

void MeasurementsTable::newMeasurement(const std::vector<std::shared_ptr<const MeasurementSequence>>& mSeq)
{
    for(const auto& mesSeq:mSeq)
    {
        vecSeq_.push_back(mesSeq);
    }

    for (unsigned long i=0; i<mSeq.size();i++)
    {
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(mSeq[i]->fileName());
        listWidget->addItem(item);
    }
}

void MeasurementsTable::activeMeasurement(const std::shared_ptr<const MeasurementSequence> mesSeq)
{

    auto it = vecSeq_.begin();
    QColor color;
    std::for_each(vecSeq_.begin(), vecSeq_.end(),
                  [&](const auto &el) {
                    color = (mesSeq == el) ? Qt::red : Qt::black;
                    listWidget->item(it++ - vecSeq_.begin())->setForeground(color);
                  });


}

void MeasurementsTable::setupUI()
{
    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(listWidget);
    setLayout(mainLayout);
}

