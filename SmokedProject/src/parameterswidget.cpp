#include "parameterswidget.h"


ParametersWidget::ParametersWidget(QWidget *parent) :
    QWidget(parent)
{
    rateBox = new QDoubleSpinBox();
    rateBox->setRange(0,5000);
    rateBox->setValue(1000);
    connect(rateBox, SIGNAL(valueChanged(double)), this, SLOT(changeRate(double)));

    startedBox = new QCheckBox();
    startedBox->setChecked(true);
    connect(startedBox, SIGNAL(clicked(bool)), this, SLOT(startAndStop(bool)));

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(rateBox);
    layout->addWidget(startedBox);

    setLayout(layout);
}

void ParametersWidget::setParticleSystem(ParticleSystem *ps)
{
    system = ps;
}


void ParametersWidget::changeRate(double r)
{
    //system->lockMutex();
    system = new ParticleSystem(system);
    system->setRate(r);
    //system->unlockMutex();
}

void ParametersWidget::startAndStop(bool b)
{
    //system->lockMutex();
    if(b)
        system->start();
    else
        system->stop();
    //system->unlockMutex();
}
