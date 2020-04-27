#include "QFileData.h"

#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QTextStream>
#include <iostream>
using namespace std;

using namespace Frederic;

QFileData::QFileData()
{

}

QFileData::~QFileData()
{
}

bool QFileData::WriteLog(const QString& QFileName, const QString& Str)
{
    if (QFileName.isEmpty()) return false;

    // 转 反斜杠(\\)为斜杠(/)
    QString FileName = TransSlash(QFileName);

    QFile File(FileName);
    if (!File.exists())
    {
        if (!CreateDir(FileName))
        {
            return false;
        }
    }
    if (File.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
    {
        QTextStream out(&File);
        out << Str << "\n";
        File.close();

        return true;
    }
    return false;
}

bool QFileData::WriteData(const QString& QFileName, void * pData, const int Size)
{
    if (QFileName.isEmpty()) return false;

    // 转 反斜杠(\\)为斜杠(/)
    QString FileName = TransSlash(QFileName);

    QFile File(FileName);
    if (!File.exists())
    {
        if (!CreateDir(FileName))
        {
            return false;
        }
    }

    if (File.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        File.write(static_cast<const char*>(pData), Size);
        File.close();
        return true;
    }

    return false;
}

bool QFileData::ReadData(const QString& QFileName, void* pData, const int Size)
{
    if (QFileName.isEmpty()) return false;

    // 转 反斜杠(\\)为斜杠(/)
    QString FileName = TransSlash(QFileName);

    QFile File(FileName);
    if (File.exists() && File.size()>= Size)
    {
        if (File.open(QIODevice::ReadOnly))
        {
            File.read(static_cast<char*>(pData), Size);
            File.close();
            return true;
        }
    }
    return false;
}

int  QFileData::FileSize(const QString& QFileName)
{
    if (QFileName.isEmpty()) return -1;

    // 转 反斜杠(\\)为斜杠(/)
    QString FileName = TransSlash(QFileName);

    QFile File(FileName);
    if (File.exists())
    {
        return (int)File.size();
    }
    return -1;
}

QString QFileData::GetYMDQString()
{
    return QDate::currentDate().toString(QString("yyyyMMdd"));
}

QString QFileData::GetYMQString()
{
    return QDate::currentDate().toString(QString("yyyyMM"));
}

QString QFileData::GetYMDHMSQString()
{
    return QDateTime::currentDateTime().toString(QString("yyyy-MM-dd HH:mm:ss "));
}

QString QFileData::GetYMDHMSZQString()
{
    return QDateTime::currentDateTime().toString(QString("yyyy-MM-dd HH:mm:ss:zzz "));
}

QString QFileData::TransSlash(const QString& Str)
{
    return QDir::fromNativeSeparators(Str);
}

bool QFileData::CreateDir(const QString& FileName)
{
    // 1. 分解字符串
	
	auto index = FileName.lastIndexOf("/");
	QString PathName(FileName);
	// 有斜杠
	if (index != -1)
	{
		PathName = (FileName.mid(0, index + 1));
	}

    QDir Dir(PathName);
    // 文件夹不存在
    if (!Dir.exists(PathName))
    {
        if (!Dir.mkpath(PathName))
        {
            return false;
        }
    }

    return true;
}
