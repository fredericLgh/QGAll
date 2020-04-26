#pragma once
#ifndef QCAMERAAPP_H_
#define QCAMERAAPP_H_
#include <QApplication>


#include "myShareMem.h"

#define pApp (static_cast<QCameraApp *>(qApp))


class QCameraApp : public QApplication
{
	Q_OBJECT
public:
	QCameraApp(int &argc, char **argv);
	~QCameraApp();

	bool IsParamOk() const;

public:

	bool ReadIni();
	void WriteIni();

private:
	void InitApp();
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

public:
	myShareMem g_mem;


};

#endif