#include "QCamGrab.h"

QCamGrab::QCamGrab(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->m_PIcID = 0;
	InitWnd();
}


void QCamGrab::InitWnd()
{
	LoadParam();
	QString Title;
	//Title = "DalsaGigEDevice (x64) - %s" + theApp.CameraName;


}
void QCamGrab::ExitWnd()
{
}

void QCamGrab::LoadParam()
{


}
