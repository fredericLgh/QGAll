#ifndef NOVICESHAREDMEMORY_H
#define NOVICESHAREDMEMORY_H

#include <QSharedMemory>
#include <string>

class CFredSharedMemory : protected QSharedMemory
{
	Q_OBJECT

public:
	CFredSharedMemory(QObject *parent = 0);
	~CFredSharedMemory();

protected:
	bool  Open(const QString& Key, int size);
	void  Close();
	void* GetBuffer();
	const void *GetBuffer() const;
protected:
	bool m_IsOpen;
};
#endif // NOVICESHAREDMEMORY_H
