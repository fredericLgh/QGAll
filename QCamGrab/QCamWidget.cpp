#include "QCamWidget.h"

QCamWidget::QCamWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(size());
	//this->m_PIcID = 0;
	InitWnd();
}


void QCamWidget::InitWnd()
{
	


	LoadParam();
	connect(ui.m_pbRecord, &QPushButton::clicked, this, &QCamWidget::OnClickedBtSave);
	connect(ui.m_pbImg, &QPushButton::clicked, this, &QCamWidget::OnClickedBtShow);
	connect(ui.m_pbSelectPath, &QPushButton::clicked, this, &QCamWidget::OnClickedBtPath);


	
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

void QCamWidget::OnClickedBtSave()
{
	qDebug() << "save";
}

void QCamWidget::OnClickedBtShow()
{
}
