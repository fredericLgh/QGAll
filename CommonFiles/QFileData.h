#ifndef QFILEDATA_H
#define QFILEDATA_H


#include <QString>

namespace Frederic
{
class QFileData
{

public:
    QFileData();
    ~QFileData();

    static bool WriteLog(const QString& QFileName, const QString& Str);

    static bool WriteData(const QString& QFileName, void* pData, const int Size);

    static bool ReadData(const QString& QFileName,  void* pData, const int Size);

    static int  FileSize(const QString& QFileName);

    // 创建文件名用到
    //20191118
    static QString GetYMDQString();

    //201911
    static QString GetYMQString();

    // 日志内容中用到的

    //2019-11-18 10:33:58
    static QString GetYMDHMSQString();

    //2019-11-18 10:33:58:020
    static QString GetYMDHMSZQString();


    // 转换 反斜杠为斜杠(Qt 中使用)
    static QString TransSlash(const QString& Str);

    // Str 是完整 目录/文件名 或者文件名
    static bool  CreateDir(const QString& Str);
};
};


#endif // !QFILEDATA_H

