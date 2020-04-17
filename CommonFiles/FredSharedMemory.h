#ifndef NOVICESHAREDMEMORY_H
#define NOVICESHAREDMEMORY_H

#include <QSharedMemory>
typedef void * HANDLE;
typedef void * LPVOID;

class CFredSharedMemory : protected QSharedMemory
{
	Q_OBJECT

public:
	CFredSharedMemory(QObject *parent = 0);
	~CFredSharedMemory();

	struct HeaderStruct
	{
		char FileMappingName[64];
		long TotalMemorySize;
		long UserMemorySize;
	};


	HANDLE m_hFileMapping;
	virtual void InitDataAtFirstTime(void);
	LPVOID m_pHeader;
	LPVOID m_pUserAddr;

public:
	bool  Open(const QString& Key, int size);
	void  Close();
	void* GetBuffer();
	const void *GetBuffer() const;
	//Struct1GlobalInfo *GetPtrGlobalInfo(void);
	//Struct1DataSpace* GetPtrDataSpace(void);


protected:
	bool m_IsOpen;

};
#endif // NOVICESHAREDMEMORY_H
