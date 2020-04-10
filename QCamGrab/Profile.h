#pragma once

/*******************************
	�ļ����ƣ�Profile.h
	�ļ������������ļ���Profile��������
	��ǰ�汾��2.2 v
	��    �ߣ�FredericLgh

*******************************/
#include <vector>
#include <QString>
#include <QRect>
class QSettings;


namespace frederic
{
	class Profile
	{

	public:
		Profile();
		~Profile();

		// ĩβ����"\\"  
		static QString GetAppPath(void);
		static bool IsFileExist(const QString &PathName);


		static bool CreateFolder(const QString& path);
		static void GetFolderFiles(std::vector<QString>& listQstring, const QString path);

		bool Attach(QString FileName, bool FullPathName = false);

		void DevideString(const QString &String, std::vector<QString> &vecString, char ch);

		QString GetParameterString(QString Section, QString Param);
		int GetParameterInt(QString Section, QString Param);
		float GetParameterFloat(QString Section, QString Param);

		//Param=aaa,bbb,ccc ��ȡ��vector�С�
		void GetParameterVecString(QString Section, QString Param, std::vector<QString> &vecString);

		//Param=100,101,102 ��ȡ��vector�С�
		void GetParameterVecInt(QString Section, QString Param, std::vector<int> &vecInt);

		//Param=20.5,40.7,60.3 ��ȡ��vector�С�
		void GetParameterVecFloat(QString Section, QString Param, std::vector<float> &vecFloat);

		void SetParameterString(QString Section, QString Param, const QString &String);
		void SetParameterInt(QString Section, QString Param, int Value);
		void SetParameterFloat(QString Section, QString Param, float Value);

		void SetParameterQRect(QString Section, QString Param, QRect rect);
		QRect GetParameterQRect(QString Section, QString Param);

	private:
		QString     m_PathName;
		QSettings*  m_pSetting;
	};

}
