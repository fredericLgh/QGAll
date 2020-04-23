#pragma once

#include <QApplication>
#include "myShareMem.h"
#include "QCamWidget.h"
#include "QCameraApp.h"
#include "QSingleMutex.h"
//��������


class QCameraApp : public QApplication
{
	Q_OBJECT
public:
	QCameraApp(int &argc, char **argv);
	~QCameraApp();

	bool IsParamOk();

public:

	bool ReadIni();
	void WriteIni();

private:
	bool InitApp();
	void ExitApp();
public:
	
	
	QString m_ClientIP;
	int       m_ImageWidth;//ÿ֡ͼ����
	int       m_ImageHeight;//ÿ֡ͼ������

	QString m_CameraName;
	int     m_ExposureTime;
	int     m_Gain;
	int m_ImageTimeout;

private:
	bool m_IsParamOk;
	myShareMem g_mem;

	//QStrin
	std::shared_ptr<QSingleMutex > m_PSingleMutex;

};

#define pApp static_cast<QCameraApp *>(qApp)
//#define g_mem static_cast<myShareMem*>(g_mem)
//extern QCameraApp theApp;
//extern myShareMem g_mem;