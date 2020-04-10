#include "QCamGrab.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QCamGrab w;
	w.show();
	return a.exec();
}
