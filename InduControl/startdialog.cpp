#include "startdialog.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <vector>
#include <QButtonGroup>
#include <QMessageBox>
#include <math.h>

//Internal Classes
#include "../InduCore/measurementsequence.h"
#include "../InduCore/measseqtc.h"
#include "../InduCore/measseqjc.h"

StartDialog::StartDialog(QWidget *parent)
    : QDialog(parent)
    , widgetTc(new QWidget(this))
    , widgetJc(new QWidget(this))
    , buttongroupmes_(new QButtonGroup(this))
    , tcbutton_(new QRadioButton("Tc Measurement", this))
    , jcbutton_(new QRadioButton("Jc Measurement", this))
    , sampleNameTc_(nullptr)
    , tempStartTc_(nullptr)
    , tempEndTc_(nullptr)
    , temperatureRateTc_(nullptr)
    , magneticFieldTc_(nullptr)
    , coilAngleTc_(nullptr)
    , frequencyTc_(nullptr)
    , voltageAmplitudeTc_(nullptr)
    , harmonicWaveTc_(nullptr)
    , sampleNameJc_(nullptr)
    , tempJc_(nullptr)
    , frequencyJc_(nullptr)
    , magneticFieldJc_(nullptr)
    , voltStartJc_(nullptr)
    , voltEndJc_(nullptr)
    , VoltRateJc_(nullptr)
    , coilAngleJc_(nullptr)
    , harmonicWaveJc_(nullptr)
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

    emit createMeasurement(vecSeq);
}

void StartDialog::setupUI()
{
    auto gridLayout = new QGridLayout();
    auto gridLayoutJc = new QGridLayout();
    auto boxButton = new QHBoxLayout();

    //Buttongroup!
    buttongroupmes_->addButton(tcbutton_);
    buttongroupmes_->addButton(jcbutton_);
    tcbutton_->setChecked(true);
    boxButton->addWidget(tcbutton_);
    boxButton->addWidget(jcbutton_);

    //Tc Measurement
    sampleNameTc_= new QLineEdit();
    sampleNameTc_->setText("");

    tempStartTc_ = new QDoubleSpinBox();
    tempStartTc_->setDecimals(2);
    tempStartTc_->setSingleStep(0.1);
    tempStartTc_->setRange(0,350);
    tempStartTc_->setValue(80);

    tempEndTc_ = new QDoubleSpinBox();
    tempEndTc_->setDecimals(2);
    tempEndTc_->setSingleStep(0.1);
    tempEndTc_->setRange(0,350);
    tempEndTc_->setValue(100);

    temperatureRateTc_ = new QDoubleSpinBox();
    temperatureRateTc_->setDecimals(2);
    temperatureRateTc_->setSingleStep(0.1);
    temperatureRateTc_->setRange(0,20);
    temperatureRateTc_->setValue(1);

    magneticFieldTc_ = new QDoubleSpinBox();
    magneticFieldTc_->setDecimals(2);
    magneticFieldTc_->setSingleStep(0.1);
    magneticFieldTc_->setRange(0,14000);
    magneticFieldTc_->setValue(0);

    coilAngleTc_ = new QDoubleSpinBox();
    coilAngleTc_->setDecimals(2);
    coilAngleTc_->setSingleStep(0.1);
    coilAngleTc_->setRange(0,360);
    coilAngleTc_->setValue(0);

    frequencyTc_ = new QDoubleSpinBox();
    frequencyTc_->setDecimals(2);
    frequencyTc_->setSingleStep(0.1);
    frequencyTc_->setRange(0,100000);
    frequencyTc_->setValue(3333.33);

    voltageAmplitudeTc_ = new QDoubleSpinBox();
    voltageAmplitudeTc_->setDecimals(3);
    voltageAmplitudeTc_->setSingleStep(0.1);
    voltageAmplitudeTc_->setRange(0,10);
    voltageAmplitudeTc_->setValue(0.1);

    harmonicWaveTc_ = new QDoubleSpinBox();
    harmonicWaveTc_->setDecimals(0);
    harmonicWaveTc_->setSingleStep(1);
    harmonicWaveTc_->setRange(1,3);
    harmonicWaveTc_->setValue(1);

    auto labelSampleName = new QLabel("Sample Name:");
    auto labelTempStart = new QLabel("Start Temperature:");
    auto labelTempEnd = new QLabel("End Temperature:");
    auto labeltemperatureRate = new QLabel("Temperature Rate:");
    auto labelMagneticField = new QLabel("Magnetic Field:");
    auto labelCoilAngle = new QLabel("Coil Angle:");
    auto labelFrequency = new QLabel("Frequency:");
    auto labelVoltageAmplitude = new QLabel("Voltage Amplitude:");
    auto labelHarmonicWave = new QLabel("Harmonic Wave:");

    gridLayout->addWidget(labelSampleName,0,0);
    gridLayout->addWidget(sampleNameTc_,0,1);
    gridLayout->addWidget(labelTempStart);
    gridLayout->addWidget(tempStartTc_);
    gridLayout->addWidget(labelTempEnd);
    gridLayout->addWidget(tempEndTc_);
    gridLayout->addWidget(labeltemperatureRate);
    gridLayout->addWidget(temperatureRateTc_);
    gridLayout->addWidget(labelMagneticField);
    gridLayout->addWidget(magneticFieldTc_);
    gridLayout->addWidget(labelCoilAngle);
    gridLayout->addWidget(coilAngleTc_);
    gridLayout->addWidget(labelFrequency);
    gridLayout->addWidget(frequencyTc_);
    gridLayout->addWidget(labelVoltageAmplitude);
    gridLayout->addWidget(voltageAmplitudeTc_);
    gridLayout->addWidget(labelHarmonicWave);
    gridLayout->addWidget(harmonicWaveTc_);

    //Jc Measurement
    sampleNameJc_= new QLineEdit();
    sampleNameJc_->setText("");

    tempJc_ = new QDoubleSpinBox();
    tempJc_->setDecimals(2);
    tempJc_->setSingleStep(0.1);
    tempJc_->setRange(0,400);
    tempJc_->setValue(80);

    voltStartJc_ = new QDoubleSpinBox();
    voltStartJc_->setDecimals(3);
    voltStartJc_->setSingleStep(0.01);
    voltStartJc_->setRange(0.004,5);
    voltStartJc_->setValue(0.010);

    voltEndJc_ = new QDoubleSpinBox();
    voltEndJc_->setDecimals(3);
    voltEndJc_->setSingleStep(0.01);
    voltEndJc_->setRange(0,5);
    voltEndJc_->setValue(2.0);

    VoltRateJc_ = new QDoubleSpinBox();
    VoltRateJc_->setDecimals(3);
    VoltRateJc_->setSingleStep(0.01);
    VoltRateJc_->setRange(0,0.1);
    VoltRateJc_->setValue(0.01);

    magneticFieldJc_ = new QDoubleSpinBox();
    magneticFieldJc_->setDecimals(2);
    magneticFieldJc_->setSingleStep(0.1);
    magneticFieldJc_->setRange(0,14000);
    magneticFieldJc_->setValue(0);

    frequencyJc_ = new QDoubleSpinBox();
    frequencyJc_->setDecimals(2);
    frequencyJc_->setSingleStep(0.1);
    frequencyJc_->setRange(0,100000);
    frequencyJc_->setValue(3333.33);

    coilAngleJc_ = new QDoubleSpinBox();
    coilAngleJc_->setDecimals(2);
    coilAngleJc_->setSingleStep(0.1);
    coilAngleJc_->setRange(0,360);
    coilAngleJc_->setValue(0);

    harmonicWaveJc_ = new QDoubleSpinBox();
    harmonicWaveJc_->setDecimals(0);
    harmonicWaveJc_->setSingleStep(1);
    harmonicWaveJc_->setRange(1,3);
    harmonicWaveJc_->setValue(1);

    auto labelSampleNameJc = new QLabel("Sample Name:");
    auto labelTempJc = new QLabel("Temperature:");
    auto labelVoltStartJc = new QLabel("Start Voltage:");
    auto labelVoltEndJc = new QLabel("End Voltage:");
    auto labelVoltageRate = new QLabel("Voltage Rate:");
    auto labelMagneticFieldJc = new QLabel("Magnetic Field:");
    auto labelCoilAngleJc = new QLabel("Coil Angle:");
    auto labelFrequencyJc = new QLabel("Frequency:");
    auto labelHarmonicWaveJc = new QLabel("Harmonic Wave:");

    gridLayoutJc->addWidget(labelSampleNameJc, 0, 0);
    gridLayoutJc->addWidget(sampleNameJc_,0,1);
    gridLayoutJc->addWidget(labelTempJc);
    gridLayoutJc->addWidget(tempJc_);
    gridLayoutJc->addWidget(labelVoltStartJc);
    gridLayoutJc->addWidget(voltStartJc_);
    gridLayoutJc->addWidget(labelVoltEndJc);
    gridLayoutJc->addWidget(voltEndJc_);
    gridLayoutJc->addWidget(labelVoltageRate);
    gridLayoutJc->addWidget(VoltRateJc_);
    gridLayoutJc->addWidget(labelMagneticFieldJc);
    gridLayoutJc->addWidget(magneticFieldJc_);
    gridLayoutJc->addWidget(labelCoilAngleJc);
    gridLayoutJc->addWidget(coilAngleJc_);
    gridLayoutJc->addWidget(labelFrequencyJc);
    gridLayoutJc->addWidget(frequencyJc_);
    gridLayoutJc->addWidget(labelHarmonicWaveJc);
    gridLayoutJc->addWidget(harmonicWaveJc_);

    //set Layouts
    widgetTc->setLayout(gridLayout);
    widgetJc->setLayout(gridLayoutJc);
    auto boxwidget = new QWidget();
    boxwidget->setLayout(boxButton);
    widgetJc->setVisible(false);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                         | QDialogButtonBox::Close);

    connect(buttongroupmes_, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
            this, &StartDialog::updateUI);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    //set MainLayout
    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(boxwidget);
    mainLayout->addWidget(widgetTc);
    mainLayout->addWidget(widgetJc);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
}

void StartDialog::updateUI()
{
    if(tcbutton_->isChecked())
    {
        widgetJc->setVisible(false);
        widgetTc->setVisible(true);
    }
    if(jcbutton_->isChecked())
    {
        widgetTc->setVisible(false);
        widgetJc->setVisible(true);
    }
}

std::vector <std::shared_ptr<const MeasurementSequence>> StartDialog::createSequence() const
{ 

    std::vector <std::shared_ptr<const MeasurementSequence>> vecSeq;
    if(tcbutton_->isChecked())
    {
        double t1 = tempStartTc_->value();
        double t2 = tempEndTc_->value();
        double t;
        if(t1>t2)
        {
            t=t2;
        }
        else
        {
            t=t1;
        }

        double rSpule = 2.21781 + t*0.07341 + pow(t,2) * -0.00641 + pow(t,3) * 2.05056E-4 +
                pow(t,4) * -1.61876E-6 + pow(t,5) * 4.14126E-9;
        double maxV = rSpule*0.5; // U=R*I  max I =0.5

        if(voltageAmplitudeTc_->value() > maxV)
        {
            QMessageBox msgBox;
            QString text1 =( "The maximum current is not allowed to surpass 0.5A. \n"
                        "The selected voltage is so high at given temperature, that it surpasses the given number.\n"
                        "The maximum Voltage is: " );
            text1.append(QString::number(maxV));

            msgBox.setText(text1);

            msgBox.exec();
        }

        else{


        MeasSeqTc seq;
        seq.setSupraName(sampleNameTc_->text());
        seq.setTempStart(tempStartTc_->value());
        seq.setTempEnd(tempEndTc_->value());
        seq.setTemperatureRate(temperatureRateTc_->value());
        seq.setMagneticField(magneticFieldTc_->value());
        seq.setCoilAngle(coilAngleTc_->value());
        seq.setFrequency(frequencyTc_->value());
        seq.setVoltageAmplitude(voltageAmplitudeTc_->value());
        seq.setHarmonicWave(harmonicWaveTc_->value());
        seq.setFileName(sampleNameTc_->text() + "_" +
                        QString::number(voltageAmplitudeTc_->value()) + "V_" +
                        QString::number(frequencyTc_->value()) + "hz_" +
                        QString::number(magneticFieldTc_->value()) + "mT_" +
                        QString::number(coilAngleTc_->value()) + "d"
                        );
        vecSeq.push_back(std::make_shared<const MeasSeqTc>(seq));
        }
    }
    else if(jcbutton_->isChecked())
    {
        double v1 = voltStartJc_->value();
        double v2 = voltEndJc_->value();
        double v;
        if(v1>v2)
        {
            v=v1;
        }
        else
        {
            v=v2;
        }
        double t=tempJc_->value();

        double rSpule = 2.21781 + t*0.07341 + pow(t,2) * -0.00641 + pow(t,3) * 2.05056E-4 +
                pow(t,4) * -1.61876E-6 + pow(t,5) * 4.14126E-9;
        double maxV = rSpule*0.5; // U=R*I  max I =0.5

        if(v > maxV)
        {
            QMessageBox msgBox;
            QString text1 =( "The maximum current is not allowed to surpass 0.5A. \n"
                        "The selected voltage is so high at given temperature, that it surpasses the given number.\n"
                        "The maximum Voltage is: " );
            text1.append(QString::number(maxV));

            msgBox.setText(text1);

            msgBox.exec();
        }
        else
        {
        MeasSeqJc seqJc;
        seqJc.setSupraName(sampleNameJc_->text());
        seqJc.setTemperature(tempJc_->value());
        seqJc.setFrequency(frequencyJc_->value());
        seqJc.setMagneticField(magneticFieldJc_->value());
        seqJc.setVoltStart(voltStartJc_->value());
        seqJc.setVoltEnd(voltEndJc_->value());
        seqJc.setVoltRate(VoltRateJc_->value());
        seqJc.setCoilAngle(coilAngleJc_->value());
        seqJc.setHarmonicWave(harmonicWaveJc_->value());
        seqJc.setFileName(sampleNameJc_->text() + "_" +
                QString::number(tempJc_->value()) + "K_" +
                QString::number(frequencyJc_->value()) + "hz_" +
                QString::number(magneticFieldJc_->value()) + "mT_" +
                QString::number(coilAngleJc_->value()) + "d"
                );

        vecSeq.push_back(std::make_shared<const MeasSeqJc>(seqJc));
        }
    }

    return vecSeq;
}
