#include "QSingleMutex.h"

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

	// ʲôʱ���ǵ����� �����ɹ�
	if (!CreateState && QSharedMemory::AlreadyExists == error())
	{
		return false;
	}

	if (!isAttached())
	{
		if (!attach())
		{
			// ��ʾ���쳣��
			return false;
		}
	}

	return true;
}