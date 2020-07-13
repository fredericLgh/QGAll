#include "FredSharedMemory.h"

CFredSharedMemory::CFredSharedMemory(QObject *parent)
: QSharedMemory(parent)
{

}

CFredSharedMemory::~CFredSharedMemory()
{
}

//void CFredSharedMemory::InitDataAtFirstTime(void)
//{
//}

bool CFredSharedMemory::Open(const QString& Key, int size)
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

void* CFredSharedMemory::GetBuffer()
{
	if (!m_IsOpen) return nullptr;

	return data();
}

const void* CFredSharedMemory::GetBuffer() const
{
	if (!m_IsOpen) return nullptr;

	return data();
}

void CFredSharedMemory::Close()
{
	if (isAttached())
	{
		detach();
	}
}
