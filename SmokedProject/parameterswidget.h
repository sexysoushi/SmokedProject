#ifndef PARAMETERSWIDGET_H
#define PARAMETERSWIDGET_H

#include "particlesystem.h"

#include <QWidget>
#include <QInputDialog>
#include <QSlider>
#include <QCheckBox>
#include <QGridLayout>

class ParametersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParametersWidget(QWidget *parent = 0);

private:
    QInputDialog* rateBox;
    QInputDialog* nbMaxBox;
    QInputDialog* maxTimeBox;
    QInputDialog* speedBox;
    QInputDialog* gravityBox;
    QSlider* spreadSlide;
    QCheckBox* startedBox;

    ParticleSystem* system;

    void setParticleSystem(ParticleSystem* ps);

signals:

public slots:
    void changeRate(double r);

};

#endif // PARAMETERSWIDGET_H
