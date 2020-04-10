#pragma once

#include <QtWidgets/QWidget>
#include "ui_QCamGrab.h"

class QCamGrab : public QWidget
{
	Q_OBJECT

public:
	QCamGrab(QWidget *parent = Q_NULLPTR);

private:
	Ui::QCamGrabClass ui;
};
