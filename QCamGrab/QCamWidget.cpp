#include "QCamWidget.h"


#include <QDebug>
#include "QPalette"

QCamWidget::QCamWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(size());
	InitWnd();
}

void QCamWidget::XferCallback(SapXferCallbackInfo * Info)
{
	QCamWidget *pDlg = (QCamWidget*)Info->GetContext();
	SapBuffer &buf = *pDlg->m_Camera.m_pBuffers;

	int t_width = buf.GetWidth();
	int t_height = buf.GetHeight();
	


	static bool ErrorSign = false;
	if (t_width != pApp->m_ImageWidth || t_height != pApp->m_ImageHeight)
	{
		if (!ErrorSign)
		{
			emit pDlg->sigchangeWaring(QString::fromLocal8Bit("图像大小（ccf）%1*%2 与 ini配置文件不符合").arg(t_width).arg(t_height));
			ErrorSign = true;
		}
	}
	//******************************* 打印帧信息 ********************************
   // int Tm;		//相机内部的时钟
   // BOOL bGetTm = Buf.GetCounterStamp(&Tm);
   // if (!bGetTm)
   // {
   //     OutputDebugStringW(L"\n Buf2 Get CounterStamp Fail!");
  //      return;
  //  }
  //  UINT32 HardwareTm = UINT32(Tm);

  //  CString str;
   // str.Format(L"\n ------ Buf2 : Index = %d, Tm = %u us", Buf.GetIndex(), HardwareTm);
   // OutputDebugStringW(str);
	//*****************************写共享内存**************************************
	Struct1GlobalInfo *pGlobal = pApp->g_mem.GetPtrGlobalInfo();
	Struct1DataSpace *p = pApp->g_mem.GetPtrDataSpace();
	//???
	long Index = p->WriteIndex;
	p->ImageArray[Index].CoilID = pGlobal->CoilID;
	p->ImageArray[Index].ViewID = pGlobal->ViewID;

	p->ImageArray[Index].FrameID = pGlobal->FrameID++;
	p->ImageArray[Index].CCDPos = pGlobal->CCDPos;

	long ImgIndex = buf.GetIndex();

	buf.Read(0, t_width*t_height, p->ImageArray[Index].RawImageBuf);

	//memcpy(p->ImageArray[Index].RawImageBuf, pData, width * height);
	Index++;

	Index %= IMAGE_ARRAY_SIZE;

	p->WriteIndex = Index;



	if (pDlg->m_SaveSign)
	{
		pDlg->m_pElapsdTimer->start();
		StructRawImage* pImage;
		long nIndex;
		pApp->g_mem.ReadRawData(pImage, nIndex);

		bool IsOk = pDlg->m_pImageEncoder->saveBMP(pDlg->m_SavePath + QString("/Pic_%1.bmp").arg(pDlg->m_PIcID, 5, 10, QChar('0')),
			pImage->RawImageBuf, pApp->m_ImageWidth, pApp->m_ImageHeight);
		//
		auto endTime = pDlg->m_pElapsdTimer->elapsed();
		if (IsOk)
		{
			emit pDlg->slotChangeElapsdTime(endTime);
		}
		else
		{
			emit pDlg->slotChangeWaring(QString::fromLocal8Bit("压缩失败！ "));
		}
		pDlg->m_PIcID++;
		pDlg->m_PIcID = pDlg->m_PIcID % 10000;

	}
}

void QCamWidget::CallBackFunction(const void *pData, int width, int height)
{

}

void QCamWidget::myCallBackConnet(SapManCallbackInfo * Info)
{

}

void QCamWidget::slotChangeCamState(bool state)
{
	SetLabel(ui.m_lbCamName, state);

}

void QCamWidget::slotChangeElapsdTime(quint64 time)
{
	ui.m_lbCompressionTime->setText(QString::number(time) + "ms");

}

void QCamWidget::slotChangeWaring(QString warning)
{
}

void QCamWidget::InitWnd()
{

	//bool isopen = m_Camera.Open(this->CallBackFunction, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), "Camera00",);

	bool isOpen = m_Camera.Open(&(QCamWidget::XferCallback), this, pApp->m_CameraName);
	
	if (isOpen)
	{
		SetupCamera();
		m_Camera.StartGrab();
		slotChangeCamState(true);
	}
	else
	{
		slotChangeCamState(false);
	}
	
	LoadParam();
	connect(ui.m_pbRecord, &QPushButton::clicked, this, &QCamWidget::OnClickedBtSave);
	connect(ui.m_pbImg, &QPushButton::clicked, this, &QCamWidget::OnClickedBtShow);
	connect(ui.m_pbSelectPath, &QPushButton::clicked, this, &QCamWidget::OnClickedBtPath);
	connect(ui.m_pbExpSetTime, &QPushButton::clicked, this, &QCamWidget::OnClickedBtExposure);
	connect(ui.m_pbGainSet, &QPushButton::clicked, this, &QCamWidget::OnClickedBtGain);

	connect(this, &QCamWidget::sigChangeCamState, this, &QCamWidget::slotChangeCamState);
	connect(this, &QCamWidget::sigChangeElapsdTime, this, &QCamWidget::slotChangeElapsdTime);

	m_pElapsdTimer = new QElapsedTimer;
	m_pTimer = new QTimer(this);
	connect(m_pTimer, &QTimer::timeout, this, &QCamWidget::TimeOut);
	m_pTimer->start(200);


}
void QCamWidget::ExitWnd()
{
}

void QCamWidget::TimeOut()
{
	//获取当前的钢卷的帧
	Struct1GlobalInfo *p = pApp->g_mem.GetPtrGlobalInfo();
	ui.m_lbCoilID->setText(QString::number(p->CoilID));
	ui.m_lbFrameID->setText(QString::number(p->FrameID));

}

void QCamWidget::LoadParam()
{
	this->setWindowTitle("DalsaGigEDevice (x64) - %s" + pApp->m_ClientIP);

	m_SavePath = Frederic::Profile::GetAppPath() + "/TempImage";
	Frederic::QFileData::CreateDir(m_SavePath);
	ui.m_lePath->setText(m_SavePath);

	ui.m_leExp->setText(QString::number(pApp->m_ExposureTime));
	ui.m_leGain->setText(QString::number(pApp->m_Gain));
	ui.m_lbCamName->setText(pApp->m_CameraName);

}

void QCamWidget::OnClickedBtPath()
{
}

void QCamWidget::OnClickedBtSave()
{
	qDebug() << "save";
}

void QCamWidget::OnClickedBtShow()
{
}

void QCamWidget::SetupCamera()
{
	auto &Device = *m_Camera.m_pAcqDevice;
	bool b = false;
	const bool InternalClockTrigger = false;
	if (InternalClockTrigger)
	{
		//设置定时器信号
		b = Device.SetFeatureValue("timerSelector", "Timer1");
		b = Device.SetFeatureValue("timerMode", "Off");
		b = Device.SetFeatureValue("timerStartSource", "Timer1End");
		b = Device.SetFeatureValue("timerDelay", 0);
		b = Device.SetFeatureValue("timerDuration", 100);		//单位：us 默认100
		b = Device.SetFeatureValue("timerMode", "Active");


		//将定时器作为相机线触发源
		b = Device.SetFeatureValue("TriggerSelector", "LineStart");
		b = Device.SetFeatureValue("TriggerMode", "On");
		b = Device.SetFeatureValue("TriggerSource", "Timer1End");
		b = Device.SetFeatureValue("TriggerOverlap", "ReadOut");
		b = Device.SetFeatureValue("triggerLineCount", 1);


		//关闭场同步
		b = Device.SetFeatureValue("TriggerSelector", "FrameStart");
		b = Device.SetFeatureValue("TriggerMode", "Off");

	}
	else
	{
		//设置 Line1 和 Line2 信号接口（绿色1+，蓝色1-，黄色2+，灰色2-）
		b = Device.SetFeatureValue("LineSelector", "Line1");
		b = Device.SetFeatureValue("LineFormat", "RS422");
		b = Device.SetFeatureValue("LineInverter", FALSE);
		b = Device.SetFeatureValue("lineDebouncingPeriod", 0);
		b = Device.SetFeatureValue("lineElectricalTermination", "Disabled");

		b = Device.SetFeatureValue("LineSelector", "Line2");
		b = Device.SetFeatureValue("LineFormat", "RS422");
		b = Device.SetFeatureValue("LineInverter", FALSE);
		b = Device.SetFeatureValue("lineDebouncingPeriod", 0);
		b = Device.SetFeatureValue("lineElectricalTermination", "Disabled");


		//设置 Line4 信号接口（紫色4+，橙色4-）
		b = Device.SetFeatureValue("LineSelector", "Line4");
		b = Device.SetFeatureValue("LineFormat", "RS422");
		b = Device.SetFeatureValue("LineMode", "Input");
		b = Device.SetFeatureValue("LineInverter", FALSE);
		b = Device.SetFeatureValue("lineDebouncingPeriod", 0);
		b = Device.SetFeatureValue("lineElectricalTermination", "Disabled");



		//设定 Line1 与 Line2 为线触发源（行同步源）
		b = Device.SetFeatureValue("TriggerSelector", "LineStart");
		b = Device.SetFeatureValue("TriggerMode", "On");
		b = Device.SetFeatureValue("TriggerSource", "rotaryEncoder1");
		b = Device.SetFeatureValue("TriggerOverlap", "ReadOut");
		b = Device.SetFeatureValue("triggerLineCount", 1);


		b = Device.SetFeatureValue("rotaryEncoderOutputMode", "Motion");	//编码器无方向
		b = Device.SetFeatureValue("rotaryEncoderInputASource", "Line1");
		b = Device.SetFeatureValue("rotaryEncoderInputBSource", "Line2");
		b = Device.SetFeatureValue("rotaryEncoderSrcActivation", "AnyEdge");
		b = Device.SetFeatureValue("rotaryEncoderMultiplier", 1);
		b = Device.SetFeatureValue("rotaryEncoderDivider", 1);


		//设定 Line4 为帧触发源（场同步源）
		b = Device.SetFeatureValue("TriggerSelector", "FrameStart");
		b = Device.SetFeatureValue("TriggerMode", "On");
		b = Device.SetFeatureValue("TriggerSource", "Line4");
		b = Device.SetFeatureValue("TriggerActivation", "RisingEdge");
	}

	//设定曝光时间
	//设定曝光时间
	b = Device.SetFeatureValue("ExposureTime", double(pApp->m_ExposureTime));		//min：4  max：3000

	//设定相机增益
	b = Device.SetFeatureValue("Gain", double(pApp->m_Gain));


	//重置硬件时间戳
	Device.SetFeatureValue("GevTimestampControlReset", TRUE);

}

void QCamWidget::OnClickedBtExposure()
{
	auto t_exp = ui.m_leExp->text().toInt();
	if (t_exp < 4 || t_exp >3000)
		return;

	pApp->m_ExposureTime = t_exp;
	//auto &t_Device = *m_Camera.m_pAcqDevice;
	////设定相机增益
	//t_Device.SetFeatureValue("ExposureTime", double(pApp->m_ExposureTime));
	int x = (int)pApp->m_ExposureTime;
	Frederic::Profile cfg;
	cfg.Attach("Client.ini");
	cfg.SetParameterInt("DalsaGigE", "ExposureTime", (int)(pApp->m_ExposureTime));
}

void QCamWidget::OnClickedBtGain()
{
	auto t_gain = ui.m_leGain->text().toInt();
	if (t_gain < 0 || t_gain >10)
		return;	

	pApp->m_Gain = (int)t_gain;
	//auto &t_Device = *m_Camera.m_pAcqDevice;
	////设定相机增益
	//t_Device.SetFeatureValue("Gain", double(pApp->m_Gain));
	Frederic::Profile cfg;
	cfg.Attach("Client.ini");
	cfg.SetParameterInt("DalsaGigE", "Gain", pApp->m_Gain);
	

}

void QCamWidget::SetLabel(QLabel*pLabel, bool state)
{
	QPalette ple;
	ple.setColor(QPalette::Background, state ? QColor(0, 255, 0) : QColor(255, 0, 0));
	pLabel->setAutoFillBackground(true);
	pLabel->setPalette(ple);

}
