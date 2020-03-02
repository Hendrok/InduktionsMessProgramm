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

/* FIXME
 * Hier kopierst du jeden shared_ptr insgesamt 3x, um ihn von mSeq in vecSeq_ zu pushen:
 *  - Das erste mal bei der Parameterübergabe per Wert (siehe Kommentar in der Header-Datei)
 *  - Das zweite mal bei for(const auto mesSeq:mseq). Die Kopie ersparst du dir mit :
 *
 *     for(const auto mesSeq:mSeq)        schlecht, erzeugt von jedem Element eine Kopie
 *     for (const auto& mesSeq : mSeq)    gut, da jedes Element per Referenz übergeben wird (d.h. keine Kopie)
 *
 *    In der zweiten Zeile habe ich auch die fehlenden Leerzeichen eingefügt
 *
 *  - Die dritte Kopie des shared_ptr findet bei push_back statt, diese Kopie ist okay)
 */
void MeasurementsTable::newMeasurement(std::vector<std::shared_ptr<const MeasurementSequence> > mSeq)
{
    for(const auto mesSeq:mSeq)
    {
        vecSeq_.push_back(mesSeq);
    }

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

/* FIXME
 * Hast du den Lambda-Ausdruck verstanden? :-D Wenn nicht, hättest du es auch bei deiner
 * Schleife (zusammen mit dem ternären Operator ?:) lassen können.
 *
 * Wenn du es aber so lässt, gehört noch eine Verbesserung hinzu (die ich in meinem Code
 * vergessen hatte:
 *    [&](const auto &el) {       anstelle von
 *    [&](auto &el) {
 *
 * , da das Element el ja gar nicht verändert wird, sondern nur im Vergleich verwendete wird
 * (alle Variablen, die nicht verändert werden, sollen als const deklariert werden):
 */
void MeasurementsTable::activeMeasurement(std::shared_ptr<const MeasurementSequence> mesSeq)
{
    auto it = vecSeq_.begin();
    QColor color;
    std::for_each(vecSeq_.begin(), vecSeq_.end(),
                  [&](auto &el) {
                    color = (mesSeq == el) ? Qt::red : Qt::black;
                    listWidget->item(it++ - vecSeq_.begin())->setForeground(color);
                  });


}

/* NOTE
 * Wenn du einen Code-Analyzer über diese Methode laufen lässt,
 * meckert er wegen veralteter Schreibweise:
 *
 *   QVBoxLayout* mainLayout = new QVBoxLayout();     nicht so gut
 *   auto mainLayout = new QVBoxLayout();             besser
 */
void MeasurementsTable::SetupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(listWidget);
    setLayout(mainLayout);
}

