#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include "particlesystem.h"

#include <QWidget>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QCheckBox>
#include <QGridLayout>

class ParametersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParametersWidget(QWidget *parent = 0);

private:
    QDoubleSpinBox* rateBox;
    QDoubleSpinBox* nbMaxBox;
    QDoubleSpinBox* maxTimeBox;
    QDoubleSpinBox* speedBox;
    QDoubleSpinBox* gravityBox;
    QSlider* spreadSlide;
    QCheckBox* startedBox;

    ParticleSystem* system;

    void setParticleSystem(ParticleSystem* ps);

signals:

public slots:
    void changeRate(double r);
    void startAndStop(bool b);

};

#endif // PARAMETERSWIDGET_H
