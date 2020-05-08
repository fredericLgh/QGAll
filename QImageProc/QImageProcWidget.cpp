#include "QImageProcWidget.h"

QImageProcWidget::QImageProcWidget(QWidget *parent)
	: QWidget(parent)
	,m_pQuerySock(nullptr)
	,m_pTimer(nullptr)
{
	ui.setupUi(this);
}


void QImageProcWidget::InitWnd()
{
}

void QImageProcWidget::ExitWnd()
{
}
