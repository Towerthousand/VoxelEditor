#include <QApplication>
#include "mainwindow.hpp"
#include <QCleanlooksStyle>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	a.setStyle(new QCleanlooksStyle);
	MainWindow w;
	w.show();
	
	return a.exec();
}

