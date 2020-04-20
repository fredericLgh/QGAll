#include "QCameraApp.h"
#include "Profile.h"
QCameraApp::QCameraApp(int &argc, char **argv)
	: QApplication(argc,argv)
{
	//��ʼ������
	//theApp = new QCameraApp();

	
	if (!ReadIni())
	{
		printf("��ȡ����ʧ��");
	}

	if (!InitApp())
	{
		printf("��ʼ��ʧ��");
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
		//����ȷ����CLient IP;
		return false;
	}

	if (m_ImageHeight < 1024 ||
		m_ImageWidth < 8192 ||
		m_ImageHeight < 100 ||
		m_ImageHeight>5000)
	{
		//����ȷ����imageWidht��Height;
		return false;
	}

	if (m_ImageTimeout == 0 || m_ImageTimeout > 60) m_ImageTimeout = 20;
	//�˴�����
	//******************** ����Ƿ��ظ����� **********************
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
