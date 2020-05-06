#include "QImageProcWidget.h"
#include "QImageProcApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	QImageProcWidget w;
	w.show();
	return a.exec();
}
