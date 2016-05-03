/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "app.h"

QT_BEGIN_NAMESPACE

class Ui_Window
{
public:
    QHBoxLayout *horizontalLayout;
    App *app;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QComboBox *emmiterType;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;

    void setupUi(QWidget *Window)
    {
        if (Window->objectName().isEmpty())
            Window->setObjectName(QStringLiteral("Window"));
        Window->resize(1025, 624);
        horizontalLayout = new QHBoxLayout(Window);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        app = new App(Window);
        app->setObjectName(QStringLiteral("app"));
        app->setEnabled(true);
        app->setMinimumSize(QSize(800, 600));
        app->setMaximumSize(QSize(800, 600));

        horizontalLayout->addWidget(app);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(Window);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 100));

        verticalLayout_2->addWidget(label);

        emmiterType = new QComboBox(Window);
        emmiterType->setObjectName(QStringLiteral("emmiterType"));

        verticalLayout_2->addWidget(emmiterType);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));

        verticalLayout_2->addLayout(verticalLayout_3);

        label_3 = new QLabel(Window);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(180, 50));
        label_3->setTextFormat(Qt::AutoText);

        verticalLayout_2->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(Window);
        QObject::connect(emmiterType, SIGNAL(currentIndexChanged(int)), Window, SLOT(selectEmitterType(int)));

        QMetaObject::connectSlotsByName(Window);
    } // setupUi

    void retranslateUi(QWidget *Window)
    {
        Window->setWindowTitle(QApplication::translate("Window", "IN55 \342\200\224 Particle System", 0));
        label->setText(QApplication::translate("Window", "<html><head/><body><p><span style=\" font-size:14pt;\">IN55\302\240\342\200\224 Particle System</span></p><p><span style=\" font-weight:600;\">How to use :</span><br/><span style=\" font-style:italic;\">Mouse + Keys </span>: move<br/><span style=\" font-style:italic;\">Alt </span>: toggle mouse capture<br/><span style=\" font-style:italic;\">Escape </span>: exit the application</p></body></html>", 0));
        emmiterType->clear();
        emmiterType->insertItems(0, QStringList()
         << QApplication::translate("Window", "Classic", 0)
         << QApplication::translate("Window", "Cone", 0)
         << QApplication::translate("Window", "Waves", 0)
        );
        label_3->setText(QApplication::translate("Window", "<html><head/><body><p><span style=\" font-size:10pt; color:#828282;\">Authors : Adrien Berthet, Gautier <br/>Claisse, Karim Naaji</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class Window: public Ui_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
