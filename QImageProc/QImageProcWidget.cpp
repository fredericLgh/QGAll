#include "QImageProcWidget.h"
#include "QImageProcApp.h"
#include "QClient1to2.h"
#include "QTimer"
#include <thread>



QImageProcWidget::QImageProcWidget(QWidget *parent)
	: QWidget(parent)
	,m_pQuerySock(nullptr)
	,m_pTimer(nullptr)
{
	ui.setupUi(this);
	InitWnd();
}


void QImageProcWidget::InitWnd()
{
	setWindowTitle(QString("ImageProcLinux - %1").arg(pApp->m_ClientIP));

	ui.m_pLableModel->setText(QString::fromLocal8Bit("����ģ�飺 %1").arg(pApp->m_DllName));

	SetLabelColor(ui.m_pLabelServer, YELLOW);

	SetStatus(3);

	//************************* �̳߳س�ʼ�� ********************************

	m_ProcessPool.CreatePool(pApp->m_GpuNum);
	m_ProcessPool.SetMaxTaskSize(6);
	//m_ProcessPool.SetThreadPriority(THREAD_PRIORITY_BELOW_NORMAL);
	TaskError Fun1 = std::bind(&QImageProcWidget::OnTaskErrorProcess, this, std::placeholders::_1);
	m_ProcessPool.SetErrFunction(Fun1);

	m_TransmitPool.CreatePool(4);
	m_TransmitPool.SetMaxTaskSize(6);
	 //m_TransmitPool.SetThreadPriority(THREAD_PRIORITY_NORMAL);
	TaskError Fun2 = std::bind(&QImageProcWidget::OnTaskErrorTransmit, this, std::placeholders::_1);
	m_TransmitPool.SetErrFunction(Fun2);

	   //************************* ���ѧϰ������� ********************************
//   if (pApp->m_hDLL)
//   {
//       typedef void(*pInitNet)(const int);
//       pInitNet pFunAddr = (pInitNet)GetProcAddress(theApp.m_hDLL, "InitNet");
//       ENSURE_EXPRESSION(pFunAddr != nullptr);

//       (pFunAddr)(theApp.m_HostThreadCount);
//   }
	//************************* �����ʼ�� ********************************
	m_pQuerySock = new QClient1to2(this);
	m_pQuerySock->TryConnect();

	m_pTimer = new QTimer(this);
	m_pTimer->setInterval(1000 * 5);
	connect(m_pTimer, &QTimer::timeout, this, &QImageProcWidget::TimeOut);
	m_pTimer->start();  //����������ʱ�� 5s

	connect(this, &QImageProcWidget::SendResultPtr, this, &QImageProcWidget::GetResultPtr);
	connect(this, &QImageProcWidget::SendMessage, this, &QImageProcWidget::GetMessage);

	//socketͨ�Ų���
	connect(m_pQuerySock, &QClient1to2::SengClientState, this, &QImageProcWidget::SetNetLampOK);
	connect(m_pQuerySock, &QClient1to2::SendTrace, this, &QImageProcWidget::WriteTrace);
	
	connect(m_pQuerySock, &QClient1to2::SendStatus, this, &QImageProcWidget::SetStatus);
	connect(m_pQuerySock, &QClient1to2::SendCCDPos, this, &QImageProcWidget::SetCCDPos);

	connect(m_pQuerySock, &QClient1to2::SendHeartbeat, this, &QImageProcWidget::GetMessage);
	connect(m_pQuerySock, &QClient1to2::SendNewCoilID, [=](QString str)
		{
			ui.m_pLabelCoilID->setText(str);
		});
	connect(this, &QImageProcWidget::SendTrace, this, &QImageProcWidget::WriteTrace, Qt::QueuedConnection);
	m_Exit = false;
	//m_LookForImageThread = std::thread(&QImageProcWidget::LookForImage, this);

}

void QImageProcWidget::ExitWnd()
{
}

void QImageProcWidget::SetLabelColor(QLabel * pLabel, const QColor & color)
{
	QPalette ple;
	ple.setColor(QPalette::Background, color);
	pLabel->setAutoFillBackground(true);
	pLabel->setPalette(ple);
	
}

void QImageProcWidget::GetResultPtr(std::shared_ptr<StructInspectResult> pResult)
{
}

void QImageProcWidget::GetMessage(UINT message, long lParam)
{
}

void QImageProcWidget::SetNetLampOK(bool IsOk)
{
}

void QImageProcWidget::SetCCDPos(long ViewID, long CCDPos)
{
}

void QImageProcWidget::WriteTrace(QString text)
{
}

void QImageProcWidget::TimeOut()
{
	// ����
	if (m_pQuerySock)
	{
		m_pQuerySock->TryConnect();
	}
}

void QImageProcWidget::LookForImage()
{
	while (!m_Exit)
	{
		HandleImage();

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

void QImageProcWidget::HandleImage()
{

	//�ô˴�
}

void QImageProcWidget::SetStatus(long status)
{
	// ����
	switch (status)
	{
	case 1:	ui.m_pBtnState->setIcon(QIcon(":/Images/Icon/StatStart_32.ico"));	    break;
	case 2:	ui.m_pBtnState->setIcon(QIcon(":/Images/Icon/StatPause_32.ico"));		break;
	case 3:	ui.m_pBtnState->setIcon(QIcon(":/Images/Icon/StatStop_32.ico"));		break;
	}
}

void QImageProcWidget::OnTaskErrorProcess(const std::string err)
{
	pApp->WriteTestLog(QString::fromLocal8Bit("RunProcessDll �ڲ�����%1").arg(err.c_str()));

	pApp->ExceptionClose();

	std::terminate();		//�Ƿ��ս����Ȩ�������û�
}

void QImageProcWidget::OnTaskErrorTransmit(const std::string err)
{
	pApp->WriteTestLog(QString::fromLocal8Bit("RunTransmit() �ڲ�����%1").arg(err.c_str()));

	pApp->ExceptionClose();

	std::terminate();		//�Ƿ��ս����Ȩ�������û�
}

