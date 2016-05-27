#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "glframe.h"
#include "mainwindow.h"
#include "parameterswidget.h"

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    GlFrame* gl;
    ParametersWidget* parameters;

    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
