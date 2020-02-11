#include "startdialog.h"
#include "../InduCore/measurementsequence.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QDialogButtonBox>
#include <QVBoxLayout>

StartDialog::StartDialog(QWidget *parent)
    : QDialog(parent)
    , tempStart_(nullptr)
    , tempEnd_(nullptr)
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

    tempStart_ = new QDoubleSpinBox();
    tempEnd_ = new QDoubleSpinBox();

    QLabel* labelTempStart = new QLabel("Start temperature:");
    QLabel* labelTempEnd = new QLabel("End Temperature:");

    gridLayout->addWidget(labelTempStart, 0, 0);
    gridLayout->addWidget(tempStart_, 0, 1);
    gridLayout->addWidget(labelTempEnd, 1, 0);
    gridLayout->addWidget(tempEnd_, 1, 1);

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
    MeasurementSequence seq;
    seq.setTempStart(tempStart_->value());
    seq.setTempEnd(tempEnd_->value());

    return std::make_shared<const MeasurementSequence>(seq);
}
