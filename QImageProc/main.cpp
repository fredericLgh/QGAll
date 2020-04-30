#include "QImageProc.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QImageProc w;
	w.show();
	return a.exec();
}
