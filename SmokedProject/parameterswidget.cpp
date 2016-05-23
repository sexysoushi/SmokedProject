#include "parameterswidget.h"


ParametersWidget::ParametersWidget(QWidget *parent) :
    QWidget(parent)
{
    rateBox = new QInputDialog();
    rateBox->setInputMode(QInputDialog::DoubleInput);
    rateBox->setDoubleRange(0,5000);
    rateBox->setDoubleValue(1000);

    connect(rateBox, SIGNAL(doubleValueChanged(double)), this, SLOT(changeRate(double)));

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(rateBox);

    setLayout(layout);
}

void ParametersWidget::setParticleSystem(ParticleSystem *ps)
{
    system = ps;
}


void ParametersWidget::changeRate(double r)
{
    system->setRate(r);
}
