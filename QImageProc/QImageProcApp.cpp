#include "QImageProcApp.h"
#include "Profile.h"
#include "QMessageBox"
#include "iostream"
#include <QDateTime>
#include "QSingleMutex.h"

QImageProcApp::QImageProcApp(int &argc,char **argv)
	: QApplication(argc,argv)
{
	InitApp();
}

QImageProcApp::~QImageProcApp()
{
}

bool QImageProcApp::IsParameterOk() const
{
	return m_IsParameterOk;
}

void QImageProcApp::InitApp()
{
	Frederic::Profile cfg;
	if (!cfg.Attach("Client.ini"))
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit(""),
			QString::fromLocal8Bit("û���ҵ������ļ�Client.ini"));
	}
	m_ImageWidth = cfg.GetParameterInt("System", "ImageWidth");
	m_ImageHeight = cfg.GetParameterInt("System", "ImageHeight");
	m_ClientIP = cfg.GetParameterString("System", "ClientIP");

	m_ServerIP = cfg.GetParameterString("System", "ServerIP");
	m_SkipFrame = cfg.GetParameterInt("System", "SkipFrame");
	m_DllName = cfg.GetParameterString("System", "Engine");
	m_DependentLibPath = cfg.GetParameterString("System", "DependentLibPath");

	if (m_ClientIP.length() < 7)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit(""),
			QString::fromLocal8Bit("���� Client.ini �ļ���������ȷ�� ClientIP"));
		return;
	}

	if (m_ImageWidth < 1024 ||
		m_ImageWidth > 8192 ||
		m_ImageHeight < 100 ||
		m_ImageHeight > 4000)
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit(""),
			QString::fromLocal8Bit("����ȷ���� ImageWidth �� ImageHeight��"));
		return;
	}

	if (m_DllName == "CoreEngine.dll")
	{
		m_HostThreadCount = 0;
	}else if (m_DllName == "DsEngine.dll")
	{
		std::vector<int> GpuIDs;
		cfg.GetParameterVecInt("DsEngine", "GpuID", GpuIDs);
		m_HostThreadCount = (int)GpuIDs.size();
		if (m_HostThreadCount == 0)
		{
			QMessageBox::critical(nullptr, QString::fromLocal8Bit(""),
				QString::fromLocal8Bit("���� Client.ini �ļ���������ȷ�� DsEngine -> GpuID"));
			return;
		}
	}else if (m_DllName == "ALiEngine.dll")
	{
		std::vector<int> GpuIDs;
		cfg.GetParameterVecInt("ALiEngine", "GpuID", GpuIDs);
		m_HostThreadCount = (int)GpuIDs.size();
		if (m_HostThreadCount == 0)
		{
			QMessageBox::critical(nullptr, QString::fromLocal8Bit(""),
				QString::fromLocal8Bit("���� Client.ini �ļ���������ȷ�� ALiEngine -> GpuID"));
			return;
		}
	}
	else
	{
		QMessageBox::critical(nullptr, QString::fromLocal8Bit(""),
			QString::fromLocal8Bit("���� Client.ini �ļ���������ȷ�� Engine"));
		return;
	}
	

	//������
	if (!g_mem.Open(m_ClientIP))
	{
		QMessageBox::critical(nullptr, "ImageProcLinuxApp",
			QString::fromLocal8Bit("�����ڴ����"));
		return;
	}
	g_mem.GetPtrGlobalInfo()->SystemStatus = 3;

	//******************** ���붯̬�� ********************
   //ע��OpenCV�ᵼ���ڴ�й¶����Ӱ���ȶ����ɺ��ԡ�

   //���� SetDllDirectory ������ https://docs.microsoft.com/zh-cn/windows/win32/api/winbase/nf-winbase-setdlldirectorya
   /*
   SetDllDirectoryW(m_DependentLibPath);
   m_hDLL = LoadLibrary(m_DllName);
   SetDllDirectoryW(nullptr);

   if ( m_hDLL == NULL )
   {
	   CString msg;
	   msg.Format(L"���� %s ʧ��!", m_DllName);
	   AfxMessageBox(msg);
	   return FALSE;
   }
   */

	m_GpuNum = cfg.GetParameterInt("AliShared", "GPUNum");
	if (m_GpuNum <= 0)
	{
		QMessageBox::critical(nullptr, "ImageProcLinuxApp",
			QString::fromLocal8Bit("����ȷ����GpuNum"));
		return;
	}
	std::vector<int> vIndex;
	std::vector<QString> VModel;
	cfg.GetParameterVecInt("AliShared", "GPUIDX", vIndex);
	cfg.GetParameterVecString("AliShared", "ModelName", VModel);
	if (vIndex.size() != VModel.size())
	{
		QMessageBox::critical(nullptr, "ImageProcLinuxApp",
			QString::fromLocal8Bit("ģ�ͺ�GPUID����ȣ�"));
		return;
	}
	if (vIndex.size() == 0)
	{
		QMessageBox::critical(nullptr, "ImageProcLinuxApp",
			QString::fromLocal8Bit("ģ�ͺ�GPUID��Ϊ0��"));
		return;
	}
#if 1
	for (int i = 0; i < vIndex.size(); ++i)
	{
		auto p = CDetectFlawClass::GetInstance();  // ��ȡʵ��
		auto path = Frederic::Profile::GetAppPath() + "/" + VModel[i];
		if (1 == p->Initialize((char*)path.toStdString().data(), vIndex[i]))
		{
			QMessageBox::critical(nullptr, "ImageProcLinuxApp",
				QString::fromLocal8Bit("%1ģ�ͳ�ʼ��ʧ�ܣ�").arg(path));

			for (auto& ref : m_vecDectFlawClass)
			{
				if (ref.first)
				{
					CDetectFlawClass::ReleaseInstance(ref.first);
					ref.first = nullptr;
				}
			}
			return;
		}
		else
		{
			m_vecDectFlawClass.push_back(std::make_pair(p, 0));
		}
	}
#endif
	m_IsParameterOk = true;


}

void QImageProcApp::ExitApp()
{
#if 1
	ExceptionClose();

#endif
}


void QImageProcApp::ExceptionClose()
{
	if (m_pSingleMutex)
	{
		m_pSingleMutex->Close();
		m_pSingleMutex = nullptr;
	}

	// �رն�̬��
	for (auto& ref : m_vecDectFlawClass)
	{
		if (ref.first)
		{
			CDetectFlawClass::ReleaseInstance(ref.first);
			ref.first = nullptr;
		}
	}


	// �رչ���  
	g_mem.Close();


	//�ر���־
	m_TestLog.EndWrite();
}

void QImageProcApp::WriteTestLog(QString Text)
{
	auto time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss");
	QString str = QString("%1 : %2 \r").arg(time).arg(Text);
	m_MutexLog.lock();
	m_TestLog.WriteLog(str);
	m_MutexLog.unlock();
}
