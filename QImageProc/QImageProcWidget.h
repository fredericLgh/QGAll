#pragma once

#include <QtWidgets/QWidget>
#include "ui_QImageProcWidget.h"
#include "myShareMem.h"
#include "SquallThreadPool.h"




class QImageProcWidget : public QWidget
{
	Q_OBJECT

public:
	QImageProcWidget(QWidget *parent = Q_NULLPTR);

private:
	Ui::QImageProcWidgetClass ui;
};
