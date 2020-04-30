#include "QCamWidget.h"


#include <QDebug>
QCamWidget::QCamWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(size());
	InitWnd();
}


void QCamWidget::CallBackFunction(const void *pData, int width, int height)
{
	static bool ErrorSign = false;
	if (width != pApp->m_ImageWidth || height != pApp->m_ImageHeight)
	{
		if (!ErrorSign)
		{
			emit sigchangeWaring(QString::fromLocal8Bit("图像大小（ccf）%1*%2 与 ini配置文件不符合").arg(width).arg(height));
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

	p->ImageArray[Index].FrameID = pGlobal->FrameID;
	p->ImageArray[Index].CCDPos = pGlobal->CCDPos;

	memcpy(p->ImageArray[Index].RawImageBuf, pData, width * height);
	Index++;

	Index %= IMAGE_ARRAY_SIZE;

	p->WriteIndex = Index;

	if (m_SaveSign)
	{
		m_pElapsdTimer->start();
		StructRawImage* pImage;
		long nIndex;
		pApp->g_mem.ReadRawData(pImage, nIndex);

		bool IsOk = m_pImageEncoder->saveBMP(m_SavePath + QString("/Pic_%1.bmp").arg(m_PIcID, 5, 10, QChar('0')),
			pImage->RawImageBuf, pApp->m_ImageWidth, pApp->m_ImageHeight);
		//
		auto endTime = m_pElapsdTimer->elapsed();
		if (IsOk)
		{
			emit slotChangeElapsdTime(endTime);
		}
		else
		{
			emit slotChangeWaring(QString::fromLocal8Bit("压缩失败！ "));
		}
		m_PIcID++;
		m_PIcID = m_PIcID % 10000;

	}






}

void QCamWidget::slotChangeCamState(bool state)
{

}

void QCamWidget::slotChangeElapsdTime(quint64 time)
{
}

void QCamWidget::slotChangeWaring(QString warning)
{
}

void QCamWidget::InitWnd()
{
	


	LoadParam();
	connect(ui.m_pbRecord, &QPushButton::clicked, this, &QCamWidget::OnClickedBtSave);
	connect(ui.m_pbImg, &QPushButton::clicked, this, &QCamWidget::OnClickedBtShow);
	connect(ui.m_pbSelectPath, &QPushButton::clicked, this, &QCamWidget::OnClickedBtPath);
	connect(ui.m_pbExpSetTime, &QPushButton::clicked, this, &QCamWidget::OnClickedBtExposure);
	connect(ui.m_pbGainSet, &QPushButton::clicked, this, &QCamWidget::OnClickedBtGain);

	connect(this, &QCamWidget::sigChangeCamState, this, &QCamWidget::slotChangeCamState);
	connect(this, &QCamWidget::sigChangeElapsdTime, this, &QCamWidget::slotChangeElapsdTime);

	

}
void QCamWidget::ExitWnd()
{
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

void QCamWidget::OnClickedBtExposure()
{
	auto t_exp = ui.m_leExp->text().toInt();
	if (t_exp < 4 || t_exp >3000)
		return;

	pApp->m_ExposureTime = t_exp;
	auto &t_Device = *m_Camera.m_pAcqDevice;
	//设定相机增益
	t_Device.SetFeatureValue("ExposureTime", double(pApp->m_ExposureTime));
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
	auto &t_Device = *m_Camera.m_pAcqDevice;
	//设定相机增益
	t_Device.SetFeatureValue("Gain", double(pApp->m_Gain));
	Frederic::Profile cfg;
	cfg.Attach("Client.ini");
	cfg.SetParameterInt("DalsaGigE", "Gain", pApp->m_Gain);
	

}
