#include "startdialog.h"
#include "../InduCore/measurementsequence.h"
#include "../InduCore/measseqtc.h"
#include "../InduCore/measseqjc.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QDialogButtonBox>
#include <QLineEdit>

StartDialog::StartDialog(QWidget *parent)
    : QDialog(parent)
    , sampleName_(nullptr)
    , tempStart_(nullptr)
    , tempEnd_(nullptr)
    , temperatureRate_(nullptr)
    , magneticField_(nullptr)
    , coilAngle_(nullptr)
    , frequency_(nullptr)
    , voltageAmplitude_(nullptr)
    , harmonicWave_(nullptr)
{
    setupUI();
}

QSize StartDialog::sizeHint() const
{
    return QSize(400, 300);
}

QSize StartDialog::minimumSizeHint() const
{
    return QSize(200, 100);
}

void StartDialog::accept()
{
    auto seq = createSequence();

    emit startMeasurement(seq);

    close();
}

void StartDialog::setupUI()
{
    //grid layout
    QGridLayout* gridLayout = new QGridLayout();

    sampleName_= new QLineEdit();
    sampleName_->setText("");

    tempStart_ = new QDoubleSpinBox();
    tempStart_->setDecimals(2);
    tempStart_->setSingleStep(0.1);
    tempStart_->setRange(0,350);
    tempStart_->setValue(80);

    tempEnd_ = new QDoubleSpinBox();
    tempEnd_->setDecimals(2);
    tempEnd_->setSingleStep(0.1);
    tempEnd_->setRange(0,350);
    tempEnd_->setValue(100);

    temperatureRate_ = new QDoubleSpinBox();
    temperatureRate_->setDecimals(2);
    temperatureRate_->setSingleStep(0.1);
    temperatureRate_->setRange(0,20);
    temperatureRate_->setValue(1);

    magneticField_ = new QDoubleSpinBox();
    magneticField_->setDecimals(2);
    magneticField_->setSingleStep(0.1);
    magneticField_->setRange(0,14000);
    magneticField_->setValue(0);

    coilAngle_ = new QDoubleSpinBox();
    coilAngle_->setDecimals(2);
    coilAngle_->setSingleStep(0.1);
    coilAngle_->setRange(0,360);
    coilAngle_->setValue(0);

    frequency_ = new QDoubleSpinBox();
    frequency_->setDecimals(2);
    frequency_->setSingleStep(0.1);
    frequency_->setRange(0,100000);
    frequency_->setValue(3333.33);

    voltageAmplitude_ = new QDoubleSpinBox();
    voltageAmplitude_->setDecimals(2);
    voltageAmplitude_->setSingleStep(0.1);
    voltageAmplitude_->setRange(0,10);
    voltageAmplitude_->setValue(0.1);

    harmonicWave_ = new QDoubleSpinBox();
    harmonicWave_->setDecimals(0);
    harmonicWave_->setSingleStep(1);
    harmonicWave_->setRange(1,3);
    harmonicWave_->setValue(1);

    QLabel* labelSampleName = new QLabel("Sample Name:");
    QLabel* labelTempStart = new QLabel("Start Temperature:");
    QLabel* labelTempEnd = new QLabel("End Temperature:");
    QLabel* labeltemperatureRate = new QLabel("Temperature Rate:");
    QLabel* labelMagneticField = new QLabel("Magnetic Field:");
    QLabel* labelCoilAngle = new QLabel("Coil Angle:");
    QLabel* labelFrequency = new QLabel("Frequency:");
    QLabel* labelVoltageAmplitude = new QLabel("Voltage Amplitude:");
    QLabel* labelHarmonicWave = new QLabel("Harmonic Wave:");

    gridLayout->addWidget(labelSampleName, 0, 0);
    gridLayout->addWidget(sampleName_, 0, 1);
    gridLayout->addWidget(labelTempStart, 1, 0);
    gridLayout->addWidget(tempStart_, 1, 1);
    gridLayout->addWidget(labelTempEnd, 2, 0);
    gridLayout->addWidget(tempEnd_, 2, 1);
    gridLayout->addWidget(labeltemperatureRate, 3, 0);
    gridLayout->addWidget(temperatureRate_, 3, 1);
    gridLayout->addWidget(labelMagneticField, 4, 0);
    gridLayout->addWidget(magneticField_, 4, 1);
    gridLayout->addWidget(labelCoilAngle, 5, 0);
    gridLayout->addWidget(coilAngle_, 5, 1);
    gridLayout->addWidget(labelFrequency, 6, 0);
    gridLayout->addWidget(frequency_, 6, 1);
    gridLayout->addWidget(labelVoltageAmplitude, 7, 0);
    gridLayout->addWidget(voltageAmplitude_, 7, 1);
    gridLayout->addWidget(labelHarmonicWave, 8, 0);
    gridLayout->addWidget(harmonicWave_, 8, 1);

    QWidget* widget = new QWidget();
    widget->setLayout(gridLayout);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                         | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(widget);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

std::shared_ptr<const MeasurementSequence> StartDialog::createSequence() const
{
    MeasSeqTc seq;

    seq.setSupraName(sampleName_->text());
    seq.setTempStart(tempStart_->value());
    seq.setTempEnd(tempEnd_->value());
    seq.setTemperatureRate(temperatureRate_->value());
    seq.setMagneticField(magneticField_->value());
    seq.setCoilAngle(coilAngle_->value());
    seq.setFrequency(frequency_->value());
    seq.setVoltageAmplitude(voltageAmplitude_->value());
    seq.setHarmonicWave(harmonicWave_->value());
    seq.setFileName(sampleName_->text() + "_" +
                    QString::number(voltageAmplitude_->value()) + "V_" +
                    QString::number(frequency_->value()) + "hz_" +
                    QString::number(magneticField_->value()) + "mT_" +
                    QString::number(coilAngle_->value()) + "d"
                    );

    return std::make_shared<const MeasSeqTc>(seq);
}
