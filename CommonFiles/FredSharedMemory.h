#ifndef CFREDSHAREDMEMORY_H
#define CFREDSHAREDMEMORY_H

#include <QSharedMemory>

#include <QString>


class CFredSharedMemory : protected QSharedMemory
{
	Q_OBJECT

public:
	explicit CFredSharedMemory(QObject *parent = 0);
	~CFredSharedMemory();

public:
	bool  Open(const QString& Key, int size);
	void  Close();
	void* GetBuffer();
	const void *GetBuffer() const;


protected:
	bool m_IsOpen;

};
#endif // CFREDSHAREDMEMORY_H
