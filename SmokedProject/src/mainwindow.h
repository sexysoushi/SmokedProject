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

// main window for Particle System demonstrator

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        // The GL Widget
        GlFrame* gl;

        // sliders for parameters
        QSlider* rateSlide;
        QSlider* nbMaxSlide;
        QSlider* maxTimeSlide;
        QSlider* speedSlide;
        QSlider* gravitySlide;
        QSlider* spreadSlide;
        QSlider* sizeSlide;

        // custom particle system commands
        QPushButton* addButton;
        QPushButton* clearButton;

        // premade effects buttons
        QPushButton* waterButton;
        QPushButton* lavaButton;
        QPushButton* smokeButton;
        QPushButton* fireworkButton;
        QPushButton* atomButton;
        QPushButton* tornadoButton;

        void keyPressEvent(QKeyEvent *event);

        void addLabel(QLayout *l, char *t1);

    signals:
        void initDone();

    private slots:
        // at startup
        void initGL();

        // custom particle system commands
        void addParticleSystem();
        void clear();

        // premade effects commands
        void addWaterSystem();
        void addLavaSystem();
        void addSmokeSystem();
        void addFireworkSystem();
        void addAtomSystem();
        void addTornadoSystem();
};

#endif // MAINWINDOW_H
