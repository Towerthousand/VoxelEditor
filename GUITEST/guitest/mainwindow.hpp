#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include <QMainWindow>

namespace Ui {
	class MainWindow;
}

class GLWidget;
class MainWindow : public QMainWindow {
		Q_OBJECT
	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
	protected:
		void keyPressEvent(QKeyEvent *event);

	private:
		Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
