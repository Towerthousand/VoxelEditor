#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);
	setWindowTitle(tr("VoxelEditor"));
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
	if (e->key() == Qt::Key_Escape)
		close();
}
