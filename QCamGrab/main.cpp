#include <QtWidgets/QApplication>
#include <QCameraApp.h>
#include "QCamWidget.h"
#include "QSingleMutex.h"
#include "QMessageBox"

int main(int argc, char *argv[])
{
	QCameraApp a(argc,argv);
	if (!a.IsParamOk())
	{
		a.quit();
		return a.exec();
	}
	QSingleMutex singleMutex(pApp->m_ClientIP + "key");
	if (!singleMutex.IsSignal())
	{
		QMessageBox::critical(nullptr, "CameraLinux " + pApp->m_ClientIP,
			QString::fromLocal8Bit("ÖØ¸´¿ªÆô£¡"));
		singleMutex.Close();
		a.quit();
		return a.exec();
	}

	QCamWidget w;
	w.show();

	return a.exec();
}
