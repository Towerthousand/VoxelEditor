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

void MainWindow::on_r0_toggled(bool checked) {
	if(checked)
		ui->renderWindow->set(0);
}

void MainWindow::on_r1_toggled(bool checked) {
	if(checked)
		ui->renderWindow->set(1);
}

void MainWindow::on_r2_toggled(bool checked) {
	if(checked)
		ui->renderWindow->set(2);
}

void MainWindow::on_r3_toggled(bool checked) {
	if(checked)
		ui->renderWindow->set(3);
}

void MainWindow::on_r4_toggled(bool checked) {
	if(checked)
		ui->renderWindow->set(4);
}

void MainWindow::on_r5_toggled(bool checked) {
	if(checked)
		ui->renderWindow->set(5);
}

void MainWindow::on_r6_toggled(bool checked) {
	if(checked)
		ui->renderWindow->set(6);
}

void MainWindow::on_r7_toggled(bool checked) {
	if(checked)
		ui->renderWindow->set(7);
}

void MainWindow::on_r8_toggled(bool checked) {
	if(checked)
		ui->renderWindow->set(8);
}

void MainWindow::on_r9_toggled(bool checked) {
	if(checked)
		ui->renderWindow->set(9);
}

void MainWindow::on_c0_colorChanged(const QColor& c) {
	ui->renderWindow->setColor(c,0);
}

void MainWindow::on_c1_colorChanged(const QColor& c) {
	ui->renderWindow->setColor(c,1);
}

void MainWindow::on_c2_colorChanged(const QColor& c) {
	ui->renderWindow->setColor(c,2);
}

void MainWindow::on_c3_colorChanged(const QColor& c) {
	ui->renderWindow->setColor(c,3);
}

void MainWindow::on_c4_colorChanged(const QColor& c) {
	ui->renderWindow->setColor(c,4);
}

void MainWindow::on_c5_colorChanged(const QColor& c) {
	ui->renderWindow->setColor(c,5);
}

void MainWindow::on_c6_colorChanged(const QColor& c) {
	ui->renderWindow->setColor(c,6);
}

void MainWindow::on_c7_colorChanged(const QColor& c) {
	ui->renderWindow->setColor(c,7);
}

void MainWindow::on_c8_colorChanged(const QColor& c) {
	ui->renderWindow->setColor(c,8);
}

void MainWindow::on_c9_colorChanged(const QColor& c) {
	ui->renderWindow->setColor(c,9);
}

void MainWindow::on_actionOpen_triggered() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
													"",
													tr("Files (*.vox*)"));
	ui->renderWindow->game.input().openFileString = fileName.toStdString();
}

void MainWindow::on_actionSave_triggered() {
	QFileDialog::setDefaultSuffix("vox");
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
													"",
													tr("Files (*.vox*)"));
	qDebug() << fileName;
	ui->renderWindow->game.input().saveFileString = fileName.toStdString();
}

void MainWindow::on_paintModeButton_pressed() {
	ui->renderWindow->game.input().mode = InputManager::PAINT;
}

void MainWindow::on_editModeButton_pressed() {
	ui->renderWindow->game.input().mode = InputManager::STANDARD;
}

void MainWindow::on_selectModeButton_pressed() {
	ui->renderWindow->game.input().mode = InputManager::SELECTION;
}

void MainWindow::on_pickModeButton_pressed() {
	ui->renderWindow->game.input().mode = InputManager::PICK;
}

void MainWindow::on_renderWindow_colorSet(const QColor &color, int option) {
	switch (option) {
		case 0:
			ui->c0->setColor(color);
			break;
		case 1:
			ui->c1->setColor(color);
			break;
		case 2:
			ui->c2->setColor(color);
			break;
		case 3:
			ui->c3->setColor(color);
			break;
		case 4:
			ui->c4->setColor(color);
			break;
		case 5:
			ui->c5->setColor(color);
			break;
		case 6:
			ui->c6->setColor(color);
			break;
		case 7:
			ui->c7->setColor(color);
			break;
		case 8:
			ui->c8->setColor(color);
			break;
		case 9:
			ui->c9->setColor(color);
			break;
		default:
			break;
	}
	ui->renderWindow->game.input().colors[option] = vec3f(float(color.red())/255.0,
														  float(color.green())/255.0,
														  float(color.blue())/255.0);
}
