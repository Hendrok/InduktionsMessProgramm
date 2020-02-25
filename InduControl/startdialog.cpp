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
    , widget(new QWidget(this))
    , widgetJc(new QWidget(this))
    , buttongroupmes_(new QButtonGroup(this))
    , tcbutton_(new QRadioButton("Tc Measurement", this))
    , jcbutton_(new QRadioButton("Jc Measurement", this))
    , sampleNameTc_(nullptr)
    , tempStart_(nullptr)
    , tempEnd_(nullptr)
    , temperatureRate_(nullptr)
    , magneticFieldTc_(nullptr)
    , coilAngleTc_(nullptr)
    , frequencyTc_(nullptr)
    , voltageAmplitude_(nullptr)
    , harmonicWaveTc_(nullptr)
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



    //close();
}

void StartDialog::setupUI()
{
    QGridLayout* gridLayout = new QGridLayout();
    QGridLayout* gridLayoutJc = new QGridLayout();
    QHBoxLayout* boxButton = new QHBoxLayout();

    //Buttongroup!
    buttongroupmes_->addButton(tcbutton_);
    buttongroupmes_->addButton(jcbutton_);
    tcbutton_->setChecked(true);
    boxButton->addWidget(tcbutton_);
    boxButton->addWidget(jcbutton_);

    //Tc Measurement
    sampleNameTc_= new QLineEdit();
    sampleNameTc_->setText("");

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

    voltageAmplitude_ = new QDoubleSpinBox();
    voltageAmplitude_->setDecimals(2);
    voltageAmplitude_->setSingleStep(0.1);
    voltageAmplitude_->setRange(0,10);
    voltageAmplitude_->setValue(0.1);

    harmonicWaveTc_ = new QDoubleSpinBox();
    harmonicWaveTc_->setDecimals(0);
    harmonicWaveTc_->setSingleStep(1);
    harmonicWaveTc_->setRange(1,3);
    harmonicWaveTc_->setValue(1);

    QLabel* labelSampleName = new QLabel("Sample Name:");
    QLabel* labelTempStart = new QLabel("Start Temperature:");
    QLabel* labelTempEnd = new QLabel("End Temperature:");
    QLabel* labeltemperatureRate = new QLabel("Temperature Rate:");
    QLabel* labelMagneticField = new QLabel("Magnetic Field:");
    QLabel* labelCoilAngle = new QLabel("Coil Angle:");
    QLabel* labelFrequency = new QLabel("Frequency:");
    QLabel* labelVoltageAmplitude = new QLabel("Voltage Amplitude:");
    QLabel* labelHarmonicWave = new QLabel("Harmonic Wave:");

    gridLayout->addWidget(labelSampleName,0,0);
    gridLayout->addWidget(sampleNameTc_,0,1);
    gridLayout->addWidget(labelTempStart);
    gridLayout->addWidget(tempStart_);
    gridLayout->addWidget(labelTempEnd);
    gridLayout->addWidget(tempEnd_);
    gridLayout->addWidget(labeltemperatureRate);
    gridLayout->addWidget(temperatureRate_);
    gridLayout->addWidget(labelMagneticField);
    gridLayout->addWidget(magneticFieldTc_);
    gridLayout->addWidget(labelCoilAngle);
    gridLayout->addWidget(coilAngleTc_);
    gridLayout->addWidget(labelFrequency);
    gridLayout->addWidget(frequencyTc_);
    gridLayout->addWidget(labelVoltageAmplitude);
    gridLayout->addWidget(voltageAmplitude_);
    gridLayout->addWidget(labelHarmonicWave);
    gridLayout->addWidget(harmonicWaveTc_);

    //Jc Measurement




    //set Layouts
    widget->setLayout(gridLayout);
    widgetJc->setLayout(gridLayoutJc);
    QWidget* boxwidget = new QWidget();
    boxwidget->setLayout(boxButton);
    widgetJc->setVisible(false);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                         | QDialogButtonBox::Close);

    connect(buttongroupmes_, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
            this, &StartDialog::updateUI);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    //set MainLayout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(boxwidget);
    mainLayout->addWidget(widget);
    mainLayout->addWidget(widgetJc);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

void StartDialog::updateUI()
{
    if(tcbutton_->isChecked())
    {
        widgetJc->setVisible(false);
        widget->setVisible(true);
    }
    if(jcbutton_->isChecked())
    {
        widget->setVisible(false);
        widgetJc->setVisible(true);
    }
}

std::vector <std::shared_ptr<const MeasurementSequence>> StartDialog::createSequence() const
{ 
    MeasSeqTc seq;
    std::vector <std::shared_ptr<const MeasurementSequence>> vecSeq;
    if(tcbutton_->isChecked())
    {

    seq.setSupraName(sampleNameTc_->text());
    seq.setTempStart(tempStart_->value());
    seq.setTempEnd(tempEnd_->value());
    seq.setTemperatureRate(temperatureRate_->value());
    seq.setMagneticField(magneticFieldTc_->value());
    seq.setCoilAngle(coilAngleTc_->value());
    seq.setFrequency(frequencyTc_->value());
    seq.setVoltageAmplitude(voltageAmplitude_->value());
    seq.setHarmonicWave(harmonicWaveTc_->value());
    seq.setFileName(sampleNameTc_->text() + "_" +
                    QString::number(voltageAmplitude_->value()) + "V_" +
                    QString::number(frequencyTc_->value()) + "hz_" +
                    QString::number(magneticFieldTc_->value()) + "mT_" +
                    QString::number(coilAngleTc_->value()) + "d"
                    );
    vecSeq.push_back(std::make_shared<const MeasSeqTc>(seq));
    }
    else if(jcbutton_->isChecked())
    {

    }









    return vecSeq;
}
