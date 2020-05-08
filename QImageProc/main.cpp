#include "QImageProcWidget.h"
#include "QImageProcApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{

	QImageProcApp a(argc, argv);
	if (!a.IsParameterOk())
	{
		a.quit();
		return a.exec();
	}
	QImageProcWidget w;
	w.show();
	return a.exec();
}
