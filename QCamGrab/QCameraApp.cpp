#include "QCameraApp.h"
#include "Profile.h"
QCameraApp::QCameraApp(int &argc, char **argv)
	: QApplication(argc,argv)
{
	//初始化界面
	//theApp = new QCameraApp();

	
	if (!ReadIni())
	{
		printf("读取参数失败");
	}

	if (!InitApp())
	{
		printf("初始化失败");
	}

	QCamGrab myDlg;
	


}



QCameraApp::~QCameraApp()
{
}

bool QCameraApp::ReadIni()
{
 	Frederic::Profile Ini;
	if (!Ini.Attach("Client.ini"))
	{
		return false;
	}
	
	m_ImageWidth = Ini.GetParameterInt("System", "ImageWidth");
	m_ImageHeight = Ini.GetParameterInt("System", "ImageHeight");
	m_ClientIP = Ini.GetParameterString("System", "ClientIP");


	m_CameraName = Ini.GetParameterString("DalsaGigE", "CameraName");
	m_ExposureTime = Ini.GetParameterInt("DalsaGigE", "ExposureTime");
	m_Gain = Ini.GetParameterInt("DalsaGigE", "Gain");
	m_ImageTimeout = Ini.GetParameterInt("DalsaGigE", "ImageTimeout");


	if (m_ClientIP.length() < 7)
	{
		//请正确配置CLient IP;
		return false;
	}

	if (m_ImageHeight < 1024 ||
		m_ImageWidth < 8192 ||
		m_ImageHeight < 100 ||
		m_ImageHeight>5000)
	{
		//请正确配置imageWidht和Height;
		return false;
	}

	if (m_ImageTimeout == 0 || m_ImageTimeout > 60) m_ImageTimeout = 20;
	//此处加锁
	//******************** 检测是否重复开启 **********************
	/*CString AppName;
	AppName.Format(L"DALSA_GIGE_DEVICE_%s", m_ClientIP);
	HANDLE AppMutex = ::CreateMutex(NULL, TRUE, AppName);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		::Beep(1000, 10);
		return FALSE;
	}
*/
	
	return  1;
}

void QCameraApp::WriteIni()
{
}

bool QCameraApp::InitApp()
{
	if (!g_mem.Open(m_ClientIP, sizeof(Struct1DataSpace)))
	{
		return 0;
	}
	return 1;
}

void QCameraApp::ExitApp()
{
}
