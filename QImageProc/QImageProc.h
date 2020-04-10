#pragma once

#include <QtWidgets/QWidget>
#include "ui_QImageProc.h"

class QImageProc : public QWidget
{
	Q_OBJECT

public:
	QImageProc(QWidget *parent = Q_NULLPTR);

private:
	Ui::QImageProcClass ui;
};
