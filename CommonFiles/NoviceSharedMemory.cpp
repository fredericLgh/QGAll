#include "NoviceSharedMemory.h"

CNoviceSharedMemory::CNoviceSharedMemory(QObject *parent)
: QSharedMemory(parent)
, m_IsOpen(false)
{

}

CNoviceSharedMemory::~CNoviceSharedMemory()
{
}

bool CNoviceSharedMemory::Open(const QString& Key, int size)
{
	setKey(Key);

	bool CreateState = create(size);

	// ����ʧ�ܲ��Ҵ��󷵻ز���(Key����)
	// ��ʾ���쳣��
	if ((!CreateState) && (QSharedMemory::AlreadyExists != error()))
	{
		m_IsOpen = false;
		return false;
	}

	if (!isAttached())
	{
		if (!attach())
		{
			m_IsOpen = false;
			return false;
		}

	}

	if (CreateState)
	{
		memset(data(), 0, size);
	}

	m_IsOpen = true;
	return true;
}

void* CNoviceSharedMemory::GetBuffer()
{
	if (!m_IsOpen) return nullptr;

	return data();
}

const void* CNoviceSharedMemory::GetBuffer() const
{
	if (!m_IsOpen) return nullptr;

	return data();
}

void CNoviceSharedMemory::Close()
{
	if (isAttached())
	{
		detach();
	}
}
