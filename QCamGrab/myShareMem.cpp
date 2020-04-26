#include "myShareMem.h"

#include <QDateTime>

myShareMem::myShareMem(QObject *parent)
	: CFredSharedMemory(parent)
{

}

myShareMem::~myShareMem()
{

}

bool myShareMem::Open(QString ClientIP)
{
	return CFredSharedMemory::Open(ClientIP, sizeof(Struct1DataSpace));
}

void myShareMem::Close(void)
{
	CFredSharedMemory::Close();
}

Struct1DataSpace* myShareMem::GetPtrDataSpace(void)
{
	auto pUserAddr = CFredSharedMemory::GetBuffer();
	Q_ASSERT(pUserAddr);
	return (Struct1DataSpace*)pUserAddr;
}

Struct1GlobalInfo* myShareMem::GetPtrGlobalInfo(void)
{
	auto pUserAddr = CFredSharedMemory::GetBuffer();
	Q_ASSERT(pUserAddr);
	return &((Struct1DataSpace*)pUserAddr)->GlobalInfo;
}

void myShareMem::WriteRawData(BYTE* pBuf, long Size)
{
	Struct1GlobalInfo* pGlobal = GetPtrGlobalInfo();
	Struct1DataSpace* p = GetPtrDataSpace();

	long Index = p->WriteIndex;

	//myShareMem::NoviceGetLocalTime(&p->ImageArray[Index].FrameTm);

	p->ImageArray[Index].CoilID = pGlobal->CoilID;
	p->ImageArray[Index].ViewID = pGlobal->ViewID;

	p->ImageArray[Index].FrameID = pGlobal->FrameID++;
	p->ImageArray[Index].CCDPos = pGlobal->CCDPos;

	Q_ASSERT(Size <= IMAGE_MAX_BUF_SIZE);
	memcpy(p->ImageArray[Index].RawImageBuf, pBuf, Size);


	Index++;
	Index %= IMAGE_ARRAY_SIZE;

	p->WriteIndex = Index;
}

void myShareMem::ReadRawData(StructRawImage* &pRaw, long &ReadIndex)
{
	Struct1DataSpace* p = GetPtrDataSpace();
	ReadIndex = (p->WriteIndex - 1 + IMAGE_ARRAY_SIZE) % IMAGE_ARRAY_SIZE;
	pRaw = &p->ImageArray[ReadIndex];
}


void myShareMem::NoviceGetLocalTime(SYSTEMTIME &time)
{
	auto current_Datetime = QDateTime::currentDateTime();

	auto Date = current_Datetime.date();

	time.wYear = (WORD)Date.year();
	time.wMonth = (WORD)Date.month();
	time.wDayOfWeek = (WORD)Date.dayOfWeek();
	time.wDay = (WORD)Date.day();

	auto Time = current_Datetime.time();
	time.wHour = (WORD)Time.hour();
	time.wMinute = (WORD)Time.minute();
	time.wSecond = (WORD)Time.second();
	time.wMilliseconds = (WORD)Time.msec();
}
