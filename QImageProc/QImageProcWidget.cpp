#include "QImageProcWidget.h"
#include "QImageProcApp.h"
#include "QClient1to2.h"
#include "QTimer"
#include <thread>
#include "QFormatConvert.h"



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
	//**********************************ͼ��ɼ��߳�************************************
	m_Exit = false;
	m_LookForImageThread = std::thread(&QImageProcWidget::LookForImage, this);

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
	qDebug() << "ptr";

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
	static long OldRawIndex = IMAGE_ARRAY_SIZE - 1;
	static long ReadFailCount = 0;


	Struct1GlobalInfo* pGlobal = pApp->g_mem.GetPtrGlobalInfo();
	StructRawImage* pRawData;
	long RawIndex;
	pApp->g_mem.ReadRawData(pRawData, RawIndex);


	if (RawIndex == OldRawIndex)
	{
		if (ReadFailCount < 90000) ReadFailCount++;

		//20����ʱ�����ң�Ϊʲô��ô��ʱ�䣿��Ϊ�����еĻ������ͣʱ����ܳ���10���ӣ�
		if (ReadFailCount == 48000)
		{
			//TRACE(L"��ʱ��δ�յ���֡��");
			//std::cout << "��ʱ��δ�յ���֡"<< std::endl;
			emit SendMessage(UM_WARNING_DATA_BREAK);
		}
		return;
	}
	else
	{
		if (ReadFailCount >= 48000)
		{
			//TRACE(L"�����յ���֡��");
			//std::cout << "�����յ���֡��"<< std::endl;
			emit SendMessage(UM_WARNING_DATA_REGAIN);
		}
		ReadFailCount = 0;
		OldRawIndex = RawIndex;
	}
	//****************** ֹͣ״̬�·��� ********************
	if (pGlobal->SystemStatus == 3)
	{
		return;
	}
	if (pGlobal->ContinuousCoilMode == 1)
	{
		if (pRawData->CoilID == 0)
		{
			return;
		}
	}
	else
	{
		if (pGlobal->ControlByNet)
		{
			if (!pGlobal->CoilInView)
			{
				return;
			}
		}
	}



	auto pInspectResult = std::make_shared<StructInspectResult>();
	if (pInspectResult)
	{
		//����ͼ�񸱱�
		pInspectResult->Img.FrameTm = pRawData->FrameTm;
		pInspectResult->Img.CoilID = pRawData->CoilID;
		pInspectResult->Img.ViewID = pRawData->ViewID;
		pInspectResult->Img.FrameID = pRawData->FrameID;
		pInspectResult->Img.CCDPos = pRawData->CCDPos;

		QFormatConvert::MonoByteToMat(pRawData->RawImageBuf, pApp->m_ImageWidth, pApp->m_ImageHeight, pInspectResult->Img.SrcImage);


		//ѹ���̳߳�

		qDebug() << "jjjj";
		TaskFunction task = std::bind(&QImageProcWidget::RunProcessDll, this, pInspectResult);
		m_ProcessPool.TryPushTask(task);
	}
	
}

void QImageProcWidget::RunProcessDll(std::shared_ptr<StructInspectResult> pResult)
{

	qDebug() << "???" << endl;


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

