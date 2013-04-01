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

	private slots:
		void on_r0_toggled(bool checked);
		void on_r1_toggled(bool checked);
		void on_r2_toggled(bool checked);
		void on_r3_toggled(bool checked);
		void on_r4_toggled(bool checked);
		void on_r5_toggled(bool checked);
		void on_r6_toggled(bool checked);
		void on_r7_toggled(bool checked);
		void on_r8_toggled(bool checked);
		void on_r9_toggled(bool checked);

		void on_c0_colorChanged(const QColor & c);
		void on_c1_colorChanged(const QColor & c);
		void on_c2_colorChanged(const QColor & c);
		void on_c3_colorChanged(const QColor & c);
		void on_c4_colorChanged(const QColor & c);
		void on_c5_colorChanged(const QColor & c);
		void on_c6_colorChanged(const QColor & c);
		void on_c7_colorChanged(const QColor & c);
		void on_c8_colorChanged(const QColor & c);
		void on_c9_colorChanged(const QColor & c);

		void on_actionOpen_triggered();
		void on_actionSave_triggered();

		void on_paintModeButton_pressed();


		void on_editModeButton_pressed();

		void on_selectModeButton_pressed();

	private:
		Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
