#pragma once

#include <QApplication>
#include "myShareMem.h"
#include "QCamGrab.h"
#include "QCameraApp.h"
//操作部分



class QCameraApp : public QApplication
{
	Q_OBJECT
public:
	QCameraApp(int &argc, char **argv);
	~QCameraApp();

public:

	bool ReadIni();
	void WriteIni();

private:
	bool InitApp();
	void ExitApp();
public:
	myShareMem g_mem;

	QString m_CameraName;
	int     m_ExposureTime;
	int     m_Gain;
	QString m_ClientIP;
	int m_ImageTimeout;

	uint       m_ImageWidth;//每帧图像宽度
	uint       m_ImageHeight;//每帧图像行数
};

#define qApp static_cast<QCameraApp*>(qApp)
//#define g_mem static_cast<myShareMem*>(g_mem)
//extern QCameraApp theApp;
//extern myShareMem g_mem;