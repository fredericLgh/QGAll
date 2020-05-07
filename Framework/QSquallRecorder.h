/*****************************************************************************

Copyright(c) 欧博科技软件部

    文件名称：QSquallRecorder.h
    文件描述：历史数据存储类
    当前版本：1.7 v
    作    者：novice Copy by Squall
    完成日期：2020-4-20
              末次修改：
              功能说明：连续历史数据存储

              注：支持写入 二进制数据、Text。

******************************************************************************/

#ifndef QSQUALLRECORDER_H
#define QSQUALLRECORDER_H

#include <QFile>
#include <QString>

class QSquallRecorder
{
public:
    enum FileLifeTime
    {
        LifeTime_Forever,		//single file
        LifeTime_Month,
        LifeTime_Day,
        LifeTime_Hour,
        LifeTime_Minute,
        };


public:
    QSquallRecorder(void);
    ~QSquallRecorder(void);

    const static short UnicodeTxtHeader = 0xFEFF;		//UNICODE文本文件头部标志
    static QString GetAppPath(void);

    void SetNameHead(QString Head);
    void SetExtendName(QString Ext);
    void SetHistoryFolder(QString Folder, bool UseFullPathFolder=false);
    bool BeginWrite(FileLifeTime lifetime=QSquallRecorder::LifeTime_Minute, int savetime=1000);
    void EndWrite(void);
    void Write(const void* lpBuf, uint nCount);			//写入数据
    void WriteLog(const QString &strLog);				//写入日志
    void DeleteExpiredFile(void);

private:
    QString GetNameByCurrentTime(void);

private:
    QFile   m_File;
    QString m_HistoryFolder;
    QString m_FileName;
    QString m_NameHead;
    QString m_ExtName;

    FileLifeTime m_LT;	//文件生存期（如：每小时一个文件）
    int m_ST;			//文件保存期限（如：保存200小时内的数据）
};

#endif // QSQUALLRECORDER_H
