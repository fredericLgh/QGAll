#include <QtWidgets/QApplication>
#include <QCameraApp.h>
#include "QCamWidget.h"

int main(int argc, char *argv[])
{
	QCameraApp a(argc,argv);
	if (!a.IsParamOk())
	{
		a.quit();
		return a.exec();
	}
	QCamWidget w;
	w.show();

	return a.exec();
}
