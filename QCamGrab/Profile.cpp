#include "profile.h"
//#include "OperateInI.h"
#include <QCoreApplication>
#include <QFileinfo>
#include <QSettings>
#include <iostream>
#include <QDir>
#include <QTextCodec>

frederic::Profile::Profile()
: m_pSetting(NULL)
{

}

frederic::Profile::~Profile()
{
	if (m_pSetting)
	{
		delete m_pSetting;
	}
}

QString frederic::Profile::GetAppPath(void)
{
	return QCoreApplication::applicationDirPath();
}

bool frederic::Profile::IsFileExist(const QString &PathName)
{
	QFileInfo fileinfo(PathName);
	return fileinfo.isFile();
}

bool frederic::Profile::Attach(QString FileName, bool FullPathName)
{
	if (FullPathName)
	{
		m_PathName = FileName;
	}
	else
	{
		m_PathName = GetAppPath() + "/" + FileName;
	}
	
	if (IsFileExist(m_PathName))
	{
		m_pSetting = new QSettings(m_PathName, QSettings::IniFormat);
		return true;
	}

	return false;
}

QString frederic::Profile::GetParameterString(QString Section, QString Param)
{

	if (!m_pSetting || !(m_pSetting->contains(Section + "/" + Param))) return QString();

	return (m_pSetting->value(Section + "/" + Param).toString());
}

int  frederic::Profile::GetParameterInt(QString Section, QString Param)
{
	if (!m_pSetting || !(m_pSetting->contains(Section + "/" + Param))) return 0;
	return (m_pSetting->value(Section + "/" + Param,0).toInt());
}

float  frederic::Profile::GetParameterFloat(QString Section, QString Param)
{
	if (!m_pSetting || !(m_pSetting->contains(Section + "/" + Param))) return 0;
	return (m_pSetting->value(Section + "/" + Param, 0).toFloat());
}

void frederic::Profile::DevideString(const QString &String, std::vector<QString> &vecString, char ch)
{
	vecString.clear();
	for (int i = 0; i < String.count();)
	{
		int end = String.indexOf(',', i);
		if (end < 0)
		{
			vecString.push_back(String.mid(i));
			break;
		}
		vecString.push_back(String.mid(i, end - i));
		i = end + 1;
	}
}

void frederic::Profile::GetParameterVecString(QString Section, QString Param, std::vector<QString> &vecString)
{
	vecString.clear();

	QString str = GetParameterString(Section, Param); 

	if (str.isEmpty()) return;

	DevideString(str, vecString, ',');
}

void frederic::Profile::GetParameterVecInt(QString Section, QString Param, std::vector<int> &vecInt)
{
	std::vector<QString> VString;
	GetParameterVecString(Section, Param, VString);

	vecInt.clear();
	for (auto ref : VString)
	{
		vecInt.push_back(ref.toInt());
	}
}

void frederic::Profile::GetParameterVecFloat(QString Section, QString Param, std::vector<float> &vecFloat)
{
	std::vector<QString> VString;
	GetParameterVecString(Section, Param, VString);

	vecFloat.clear();
	for (auto ref : VString)
	{
		vecFloat.push_back(ref.toFloat());
	}
}

void frederic::Profile::SetParameterString(QString Section, QString Param, const QString &String)
{
	if (!m_pSetting || !(m_pSetting->contains(Section + "/" + Param))) return;
	m_pSetting->setValue(Section + "/" + Param, String);
}

void frederic::Profile::SetParameterInt(QString Section, QString Param, int Value)
{
	if (!m_pSetting || !(m_pSetting->contains(Section + "/" + Param))) return;
	m_pSetting->setValue(Section + "/" + Param, Value);
}

void frederic::Profile::SetParameterFloat(QString Section, QString Param, float Value)
{
	if (!m_pSetting || !(m_pSetting->contains(Section + "/" + Param))) return;
	m_pSetting->setValue(Section + "/" + Param, QString("%1").arg(Value));
}

void  frederic::Profile::SetParameterQRect(QString Section, QString Param, QRect rect)
{
	if (!m_pSetting || !(m_pSetting->contains(Section + "/" + Param))) return;
	m_pSetting->setValue(Section + "/" + Param, rect);
}

QRect  frederic::Profile::GetParameterQRect(QString Section, QString Param)
{
	if (!m_pSetting || !(m_pSetting->contains(Section + "/" + Param))) return QRect();
	return (m_pSetting->value(Section + "/" + Param).toRect());
}


bool frederic::Profile::CreateFolder(const QString& path)
{
	QString PathName = path;
	if (PathName.isEmpty()) return false;

	QDir CheckDir;
	if (CheckDir.exists(PathName)) return true;

	int Index = 0;
	while (Index < PathName.size() && Index != -1)
	{
		Index = PathName.indexOf("\\", Index);
		QString pathNameTemp = Index == -1 ? PathName : PathName.mid(0, Index++);

		if (!CheckDir.exists(pathNameTemp) && !CheckDir.mkdir(pathNameTemp))
		{
			break;
		}
	}

	return CheckDir.exists(PathName);
}

void frederic::Profile::GetFolderFiles(std::vector<QString>& listQstring, const QString path)
{
	listQstring.clear();
	QDir dir(path);
	auto& listName = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
	for (auto ref : listName)
	{
		listQstring.push_back(ref);
	}
}