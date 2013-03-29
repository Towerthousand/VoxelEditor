#include <QtGui>
#include <QtOpenGL>
#include <math.h>
#include "glwidget.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809D
#endif

GLWidget::GLWidget(QWidget *parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), parent), timer(0), focus(true){
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	timer->start(0);
}

GLWidget::~GLWidget() {
	game.close();
}

void GLWidget::initializeGL() {
	game.input().resizeWindow(this->height(),this->width());
	if (game.init()) {
		game.setScene(new SceneMain(game));
	}
}

void GLWidget::paintGL() {
	game.update(clock.restart().asSeconds());
	game.draw();
}

void GLWidget::resizeGL(int width, int height) {
	if (focus) game.input().resizeWindow(height,width);
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
	if (focus) game.input().pressMouse(event->button());
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event) {
	if (focus) game.input().releaseMouse(event->button());
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
	if (focus) game.input().moveMouse(event->x(),event->y());
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
	if (focus) game.input().pressKey((Qt::Key)event->key());
}

void GLWidget::keyReleaseEvent(QKeyEvent *event) {
	if (focus) game.input().releaseKey((Qt::Key)event->key());
}

void GLWidget::enterEvent(QEvent *event) {
	QPoint newMousePos = this->mapFromGlobal(this->cursor().pos());
	game.input().setMousePos(newMousePos.x(),newMousePos.y());
}

void GLWidget::focusInEvent(QFocusEvent *event) {
	game.input().gainFocus();
	focus = true;
}

void GLWidget::focusOutEvent(QFocusEvent *event) {
	game.input().loseFocus();
	focus = false;
}

void GLWidget::set0() {
	game.input().selectedColor = 0;
}

void GLWidget::set1() {
	game.input().selectedColor = 1;
}

void GLWidget::set2() {
	game.input().selectedColor = 2;
}

void GLWidget::set3() {
	game.input().selectedColor = 3;
}

void GLWidget::set4() {
	game.input().selectedColor = 4;
}

void GLWidget::set5() {
	game.input().selectedColor = 5;
}

void GLWidget::set6() {
	game.input().selectedColor = 6;
}

void GLWidget::set7() {
	game.input().selectedColor = 7;
}

void GLWidget::set8() {
	game.input().selectedColor = 8;
}

void GLWidget::set9() {
	game.input().selectedColor = 9;
}

void GLWidget::set10() {
	game.input().selectedColor = 10;
}

void GLWidget::set11() {
	game.input().selectedColor = 11;
}

void GLWidget::setColor0(const QColor &color) {
	game.input().colors[0] = vec3f(float(color.red())/255.0,float(color.green())/255.0,float(color.blue())/255.0);
}

void GLWidget::setColor1(const QColor &color) {
	game.input().colors[1] = vec3f(float(color.red())/255.0,float(color.green())/255.0,float(color.blue())/255.0);
}

void GLWidget::setColor2(const QColor &color) {
	game.input().colors[2] = vec3f(float(color.red())/255.0,float(color.green())/255.0,float(color.blue())/255.0);
}

void GLWidget::setColor3(const QColor &color) {
	game.input().colors[3] = vec3f(float(color.red())/255.0,float(color.green())/255.0,float(color.blue())/255.0);
}

void GLWidget::setColor4(const QColor &color) {
	game.input().colors[4] = vec3f(float(color.red())/255.0,float(color.green())/255.0,float(color.blue())/255.0);
}

void GLWidget::setColor5(const QColor &color) {
	game.input().colors[5] = vec3f(float(color.red())/255.0,float(color.green())/255.0,float(color.blue())/255.0);
}

void GLWidget::setColor6(const QColor &color) {
	game.input().colors[6] = vec3f(float(color.red())/255.0,float(color.green())/255.0,float(color.blue())/255.0);
}

void GLWidget::setColor7(const QColor &color) {
	game.input().colors[7] = vec3f(float(color.red())/255.0,float(color.green())/255.0,float(color.blue())/255.0);
}

void GLWidget::setColor8(const QColor &color) {
	game.input().colors[8] = vec3f(float(color.red())/255.0,float(color.green())/255.0,float(color.blue())/255.0);
}

void GLWidget::setColor9(const QColor &color) {
	game.input().colors[9] = vec3f(float(color.red())/255.0,float(color.green())/255.0,float(color.blue())/255.0);
}

void GLWidget::setColor10(const QColor &color) {
	game.input().colors[10] = vec3f(float(color.red())/255.0,float(color.green())/255.0,float(color.blue())/255.0);
}

void GLWidget::setColor11(const QColor &color) {
	game.input().colors[11] = vec3f(float(color.red())/255.0,float(color.green())/255.0,float(color.blue())/255.0);
}

