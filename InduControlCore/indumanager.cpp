#include "indumanager.h"
#include <QDebug>


//Eigene Klassen
#include "../InduCore/filewriter.h"
#include "../InduCore/measurementsequence.h"
#include <QDir>
InduManager::InduManager()
{

}

void InduManager::startMeasurement(std::shared_ptr<MeasurementSequence> measurementSequence)
{

    FileWriter fw;
    fw.writeFileName(measurementSequence);
    QString path("SimulationsMessungen/");
    QDir dir;  // ich erstelle QString mit dem Ordner, danach die direction
    if (!dir.exists(path)) // Wenn nötig wird der Ordner erstellt
        dir.mkpath(path); // You can check the success if needed


    QFile file(path + measurementSequence->fileName() + ".txt");
    file.open(QIODevice::WriteOnly);

    QString filepath=file.fileName();




    fw.openFile(measurementSequence,filepath);

    qDebug()<<filepath;

}
