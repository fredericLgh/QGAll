#include "QCamGrab.h"
#include <QtWidgets/QApplication>
#include <QCameraApp.h>
#include <QSingleMutex.h>

int main(int argc, char *argv[])
{

	QSingleMutex single("QCameraGrab");
	if (!single.IsSignal())
	{
		QApplication app(argc, argv);
		QMessageBox;
		return app.exec();
	}
	QCameraApp a(argc,argv);
	QCamGrab w;
	w.show();
	return a.exec();



	QApplication a(argc, argv);
	QCamGrab w;
	w.show();
	return a.exec();
}
