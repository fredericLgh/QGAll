#include "QCamWidget.h"

QCamWidget::QCamWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->m_PIcID = 0;
	InitWnd();
}


void QCamWidget::InitWnd()
{
	LoadParam();
	QString Title;
	//Title = "DalsaGigEDevice (x64) - %s" + theApp.CameraName;
}
void QCamWidget::ExitWnd()
{
}

void QCamWidget::LoadParam()
{


}
