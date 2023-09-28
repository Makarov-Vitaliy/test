#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QCoreApplication::setOrganizationName("MO");
	QCoreApplication::setApplicationName("Server");
	MainWindow w;
	w.show();
	return a.exec();
}
