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
#include <vector>
#include <QButtonGroup>


StartDialog::StartDialog(QWidget *parent)
    : QDialog(parent)
    , buttongroupmes_(new QButtonGroup(this))
    , tcbutton_(new QRadioButton("Tc Measurement", this))
    , jcbutton_(new QRadioButton("Jc Measurement", this))
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
    auto vecSeq = createSequence();

    emit createMeasurement(vecSeq);  //-> weiter gehts bei Mainwindow bei onCreateMeasurement



    close();
}

void StartDialog::setupUI()
{
    //grid layout
    QGridLayout* gridLayout = new QGridLayout();

    //Buttongroup!
    buttongroupmes_->addButton(tcbutton_);
    buttongroupmes_->addButton(jcbutton_);
    tcbutton_->setChecked(true);

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

    gridLayout->addWidget(tcbutton_,0,0);
    gridLayout->addWidget(jcbutton_,0,1);


    if(tcbutton_->isChecked())
    {
    gridLayout->addWidget(labelSampleName);
    gridLayout->addWidget(sampleName_);
    gridLayout->addWidget(labelTempStart);
    gridLayout->addWidget(tempStart_);
    gridLayout->addWidget(labelTempEnd);
    gridLayout->addWidget(tempEnd_);
    gridLayout->addWidget(labeltemperatureRate);
    gridLayout->addWidget(temperatureRate_);
    gridLayout->addWidget(labelMagneticField);
    gridLayout->addWidget(magneticField_);
    gridLayout->addWidget(labelCoilAngle);
    gridLayout->addWidget(coilAngle_);
    gridLayout->addWidget(labelFrequency);
    gridLayout->addWidget(frequency_);
    gridLayout->addWidget(labelVoltageAmplitude);
    gridLayout->addWidget(voltageAmplitude_);
    gridLayout->addWidget(labelHarmonicWave);
    gridLayout->addWidget(harmonicWave_);
    }

    else if(jcbutton_->isChecked())
    {
    gridLayout->addWidget(labelSampleName);
    gridLayout->addWidget(sampleName_);
    }


    QWidget* widget = new QWidget();
    widget->setLayout(gridLayout);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                         | QDialogButtonBox::Cancel);

    connect(buttongroupmes_, &QButtonGroup::checkedButton, this, &StartDialog::setupUI);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(widget);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

std::vector <std::shared_ptr<const MeasurementSequence>> StartDialog::createSequence() const
{ 
    MeasSeqTc seq;

    if(tcbutton_->isChecked())
    {

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
    }
    else if(jcbutton_->isChecked())
    {

    }





    std::vector <std::shared_ptr<const MeasurementSequence>> vecSeq;
    vecSeq.push_back(std::make_shared<const MeasSeqTc>(seq));


    return vecSeq;
}
