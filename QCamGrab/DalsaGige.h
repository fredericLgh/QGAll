#ifndef QDALSAGIGE_H_
#define QDALSAGIGE_H_

#include "SapClassBasic.h"
#pragma comment(lib,"SapClassBasic.lib")
#include <QString>
#include <thread>

class QDalsaGige
{
public:
	QDalsaGige();
	~QDalsaGige();

	static bool FindGigE(const QString &UserName, int &ServerIndex);
	static bool IsCameraAccessible(const QString &UserName);
	static bool IsCameraAvailable(int ServerIndex);

	//bool Open(GEVEVENT_CBFUNCTION pFunction, LPVOID pUser, const QString &UserName);
	bool Open(SapXferCallback pFunction, LPVOID pUser, const QString &UserName,
		UINT width = 4096, UINT height = 1, BOOL isUseTurboDrive = FALSE);
	void Close(void);
	bool IsOpen(void);
	bool IsAccessible(void);

	bool StartGrab(void);
	void StopGrab(void);
	BOOL PrintFeatures(void);

public:
	SapAcqDevice*     m_pAcqDevice;   //Ïà»úµÄlib
	SapBuffer*        m_pBuffers;
	SapTransfer*      m_pXfer;
	bool m_isExit;

protected:
	void ClearResource(void);
	bool  m_bOpen;
	QString m_cameraName;
	void SetImageSize(void);

	
};


#endif