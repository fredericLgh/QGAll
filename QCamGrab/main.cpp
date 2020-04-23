#include "QCamWidget.h"
#include <QtWidgets/QApplication>
#include <QCameraApp.h>
#include <QSingleMutex.h>

int main(int argc, char *argv[])
{

	QSingleMutex single("QCameraGrab");
	if (!single.IsSignal())
	{
		QApplication app(argc, argv);
		return app.exec();
	}
	QCameraApp a(argc,argv);
	QCamWidget w;
	w.show();
	return a.exec();
}
