#include "QCameraApp.h"
#include "Profile.h"
QCameraApp::QCameraApp(int &argc, char **argv)
	: QApplication(argc,argv)
{


}

QCameraApp::~QCameraApp()
{
}

bool QCameraApp::ReadIni()
{
	frederic::Profile Ini;
	if (Ini.Attach("CameraParam.ini"))
	{
		CameraName = Ini.GetParameterString("CameraParam", "CameraNameL");
		//m_RightCameraName = Ini.GetParameterString("CameraParam", "CameraNameR");

		m_ImageWidth = Ini.GetParameterInt("CameraParam", "ImageWidth");
		//m_ImageHeight = Ini.GetParameterInt("CameraParam", "ImageHeight");

		m_ExpTime = Ini.GetParameterInt("CameraParam", "ExposureTimeL");
		//m_RightExpTime = Ini.GetParameterInt("CameraParam", "ExposureTimeR");

		m_Gain = Ini.GetParameterInt("CameraParam", "GainL");
		//m_RightGain = Ini.GetParameterInt("CameraParam", "GainR");
	}

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

}

void QCameraApp::WriteIni()
{
}

bool QCameraApp::InitApp()
{
	return ReadIni();
}

void QCameraApp::ExitApp()
{
}
