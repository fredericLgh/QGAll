#pragma once

#include <QApplication>
#include "myShareMem.h"
#include "QCamGrab.h"
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
	QString CameraName;
	int     m_ExpTime;
	int     m_Gain;
	QString m_ClientIP;

	uint       m_ImageWidth;//每帧图像宽度
	uint       m_ImageHeight;//每帧图像行数
};

#define pApp static_cast<QCameraGrabApp*>(qApp)
#define g_mem static_cast<myShareMem*>(g_mem)
//extern QCameraApp theApp;
//extern myShareMem g_mem;