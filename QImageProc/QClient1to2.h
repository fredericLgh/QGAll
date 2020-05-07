#pragma once
#include <QTcpSocket>

class QClient1to2 :
	public QTcpSocket
{
	Q_OBJECT
public:
	QClient1to2(QObject* parent);
	~QClient1to2();

};

