#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	/* Add the render widget to the window */
	app = new App;
	app->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	app->setFocusPolicy(Qt::StrongFocus);
	app->setFocus();
	app->init();

	ui->centralwidget = app;

	/*QHBoxLayout *mainLayout;
	mainLayout = qobject_cast<QHBoxLayout *>(ui->centralwidget->layout());
	mainLayout->addWidget(app);

	/* Init particle */
}

MainWindow::~MainWindow()
{
	delete ui;
}
