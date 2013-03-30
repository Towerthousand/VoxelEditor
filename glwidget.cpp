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
	QPoint newMousePos = this->mapFromGlobal(this->cursor().pos());
	game.input().setMousePos(newMousePos.x(),newMousePos.y());
}

void GLWidget::focusOutEvent(QFocusEvent *event) {
	game.input().loseFocus();
	focus = false;
	QPoint newMousePos = this->mapFromGlobal(this->cursor().pos());
	game.input().setMousePos(newMousePos.x(),newMousePos.y());
}

void GLWidget::set(int option) {
	game.input().selectedColor = option;
}

void GLWidget::setColor(const QColor &color,int option) {
	game.input().colors[option] = vec3f(float(color.red())/255.0,float(color.green())/255.0,float(color.blue())/255.0);
}
