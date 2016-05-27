#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "glframe.h"
#include "mainwindow.h"

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>



class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        GlFrame* gl;

        QSlider* rateSlide;
        QSlider* nbMaxSlide;
        QSlider* maxTimeSlide;
        QSlider* speedSlide;
        QSlider* gravitySlide;
        QSlider* spreadSlide;

        QPushButton* addButton;
        QPushButton* clearButton;


        void keyPressEvent(QKeyEvent *event);

        void addLabel(QLayout *l, char *t1);

signals:
        void initDone();

private slots:
        void initGL();
        void addParticleSystem();
        void clear();
};

#endif // MAINWINDOW_H
