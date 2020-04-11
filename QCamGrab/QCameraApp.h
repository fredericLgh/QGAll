#pragma once

#include <QApplication>
#include "FredSharedMemory.h"

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

extern QCameraApp theApp;
extern CFredSharedMemory g_mem;