#include "QSingleMutex.h"
#include "iostream"

QSingleMutex::QSingleMutex(const QString& Name, QObject *parent)
	: QSharedMemory(parent)
	, m_Key(Name)
{
}

QSingleMutex::~QSingleMutex()
{
	if (isAttached())
	{
		detach();
	}
}

bool QSingleMutex::IsSignal()
{
	setKey(m_Key);

	bool CreateState = create(1);

	// 什么时候是单例？ 创建成功
	if (!CreateState && QSharedMemory::AlreadyExists == error())
	{
		return false;
	}

	if (!isAttached())
	{
		if (!attach())
		{
			// 表示出异常了
			return false;
		}
	}

	return true;
}

void QSingleMutex::Close()
{
	if (isAttached())
	{
		detach();
	}

	std::cout << "~QSingleMutex" << std::endl;
	QMessageBox::critical(nullptr, "~QSingleMutex",
		QString::fromLocal8Bit("QSingleMutex 析构"));
}
