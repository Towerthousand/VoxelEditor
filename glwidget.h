#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "Game.hpp"
class QtLogo;

class GLWidget : public QGLWidget {
		Q_OBJECT
	public:
		GLWidget(QWidget *parent = 0);
		~GLWidget();
		void set(int option);
		void setColor(const QColor &color, int option);

	protected:
		void initializeGL();
		void paintGL();
		void resizeGL(int width, int height);

		void mousePressEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void keyPressEvent(QKeyEvent *event);
		void keyReleaseEvent(QKeyEvent *event);
		void enterEvent(QEvent *event);
		void focusInEvent(QFocusEvent *event);
		void focusOutEvent(QFocusEvent *event);

	private:
		sf::Clock clock;
		QTimer* timer;
		Game game;
		bool focus;
};

#endif
