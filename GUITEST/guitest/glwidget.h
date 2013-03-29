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

	public slots:
		void set0();
		void set1();
		void set2();
		void set3();
		void set4();
		void set5();
		void set6();
		void set7();
		void set8();
		void set9();
		void set10();
		void set11();

		void setColor0(const QColor &color);
		void setColor1(const QColor &color);
		void setColor2(const QColor &color);
		void setColor3(const QColor &color);
		void setColor4(const QColor &color);
		void setColor5(const QColor &color);
		void setColor6(const QColor &color);
		void setColor7(const QColor &color);
		void setColor8(const QColor &color);
		void setColor9(const QColor &color);
		void setColor10(const QColor &color);
		void setColor11(const QColor &color);

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
