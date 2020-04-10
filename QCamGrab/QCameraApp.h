#pragma once

#include <QApplication>

class QCameraApp : public QApplication
{
	Q_OBJECT
public:
	QCameraApp(int &argc, char **argv);
	~QCameraApp();


public:

	void ReadIni();
	void WriteIni();

private:
	void InitApp();
	void ExitApp();
public:
	QString CameraName;
	int     m_ExpTime;
	int     m_Gain;

	uint       m_ImageWidth;//ÿ֡ͼ����
	uint       m_ImageHeight;//ÿ֡ͼ������
};
