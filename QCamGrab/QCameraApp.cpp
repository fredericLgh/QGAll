#include "QCameraApp.h"
#include "Profile.h"
#include <QMessageBox>

QCameraApp::QCameraApp(int &argc, char **argv)
	: QApplication(argc,argv)
	,m_IsParamOk(false)
{
	InitApp();
}



QCameraApp::~QCameraApp()
{
	ExitApp();
}

bool QCameraApp::IsParamOk() const
{
	return m_IsParamOk;
}

bool QCameraApp::ReadIni()
{
 	Frederic::Profile cfg;
	if (!cfg.Attach("Client.ini"))
	{
		if (!cfg.Attach("Client.ini"))
		{
			QMessageBox::critical(nullptr, QString::fromLocal8Bit(""),
				QString::fromLocal8Bit("û���ҵ������ļ� Client.ini"));
			return false;
		}
	}
	
	m_ImageWidth = cfg.GetParameterInt("System", "ImageWidth");
	m_ImageHeight = cfg.GetParameterInt("System", "ImageHeight");
	m_ClientIP = cfg.GetParameterString("System", "ClientIP");


	m_CameraName = cfg.GetParameterString("DalsaGigE", "CameraName");
	m_ExposureTime = cfg.GetParameterInt("DalsaGigE", "ExposureTime");
	m_Gain = cfg.GetParameterInt("DalsaGigE", "Gain");
	m_ImageTimeout = cfg.GetParameterInt("DalsaGigE", "ImageTimeout");


	if (m_ClientIP.length() < 7)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit(""),
			QString::fromLocal8Bit("���� Client.ini �ļ���������ȷ�� ClientIP"));
		return false;
	}

	if (m_ImageWidth < 1024 ||
		m_ImageWidth > 8192 ||
		m_ImageHeight < 100 ||
		m_ImageHeight>5000)
	{
		//����ȷ����imageWidht��Height;
		QMessageBox::critical(nullptr, QString::fromLocal8Bit(""),
			QString::fromLocal8Bit("����ȷ���� ImageWidth �� ImageHeight��"));
		return false;
	}

	if (m_ImageTimeout == 0 || m_ImageTimeout > 60) m_ImageTimeout = 20;
	//�˴�����
	//******************** ����Ƿ��ظ����� **********************
	
	return  true;
}

void QCameraApp::WriteIni()
{
	
}

void QCameraApp::InitApp()
{
	if (!ReadIni())
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit(""),
			QString::fromLocal8Bit("�����ļ���дʧ�ܣ�"));
	}
	;
	if (!g_mem.Open(m_ClientIP))
	{
		QMessageBox::critical(nullptr, "CameraLinux",
			QString::fromLocal8Bit("�����ڴ����"));
			return;
	}
	m_IsParamOk = true;
}

void QCameraApp::ExitApp()
{
	if (m_IsParamOk)
	{
		g_mem.Close();
	}
}
