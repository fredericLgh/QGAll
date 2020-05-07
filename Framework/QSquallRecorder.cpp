#include "QSquallRecorder.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QMessageBox>

#include "OperateINI.h"

#include <QTextStream>

QSquallRecorder::QSquallRecorder()
    : m_NameHead("MyRec")
    , m_ExtName("dat")
    , m_LT(LifeTime_Minute)
    , m_ST(1000)
{
    m_HistoryFolder = GetAppPath();
}

QSquallRecorder::~QSquallRecorder()
{

}

QString QSquallRecorder::GetAppPath(void)
{
   return QCoreApplication::applicationDirPath();
}


void QSquallRecorder::SetNameHead(QString Head)
{
   m_NameHead = Head;
}

void QSquallRecorder::SetExtendName(QString Ext)
{
   m_ExtName = Ext;
}

void QSquallRecorder::SetHistoryFolder(QString Folder, bool UseFullPathFolder)
{

}

bool QSquallRecorder::BeginWrite(FileLifeTime lifetime, int savetime)
{
    m_LT = lifetime;
    m_ST = savetime;


    bool isok =  novice::COperateINI::CreateFolder(m_HistoryFolder);
    if(!isok)
    {
        QMessageBox::critical(nullptr,m_HistoryFolder,
                              QString::fromLocal8Bit("历史数据文件夹创建失败!"));
        return false;
    }


    m_FileName = GetNameByCurrentTime();

    QString PN;
    PN = m_HistoryFolder + "/" +  m_FileName;

    m_File.setFileName(PN);

    if (m_File.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void QSquallRecorder::EndWrite(void)
{
    if(m_File.isOpen())
    {
      m_File.close();
    }
}

void QSquallRecorder::Write(const void* lpBuf, uint nCount)
{
    if ( m_File.isOpen() )
    {
        QString temp = GetNameByCurrentTime();

        if ( temp == m_FileName )
        {
            m_File.write(static_cast<const char*>(lpBuf), nCount);
        }
        else
        {
            EndWrite();

            if ( BeginWrite( m_LT, m_ST ) )
            {
                m_File.write(static_cast<const char*>(lpBuf), nCount);
            }

            DeleteExpiredFile();
        }
    }
}

void QSquallRecorder::WriteLog(const QString &strLog)
{
    if (m_File.isOpen())
    {
        QString temp = GetNameByCurrentTime();

        if ( temp == m_FileName)
        {
            QTextStream out(&m_File);
            out << strLog;
        }
        else
        {
            EndWrite();
            if (BeginWrite(m_LT, m_ST))
            {
                QTextStream out(&m_File);
                out << strLog;
            }

            DeleteExpiredFile();
        }
    }
}

//以后再写
void QSquallRecorder::DeleteExpiredFile(void)
{
    Q_ASSERT(m_LT != LifeTime_Forever);

    auto datetime = QDateTime::currentDateTime();
    QDateTime oldt;
    QString oldFile;

    // 2020 04 20 17 33
    auto p = [](QDateTime &date)->int
    {
        int value = date.date().year();
        value = value*100 + date.date().month();
        value = value*100 + date.date().day();
        value = value*100 + date.time().hour();
        value = value*100 + date.time().minute();
        return value;
    };

    int timeInt = p(datetime);

    QDir dir;
    //m_HistoryFolder   m_ExtName
    auto listName = dir.entryList(QDir::Files|QDir::NoDotAndDotDot);
    for(auto iter = listName.begin();iter != listName.end();)
    {
        if(iter->contains(m_ExtName) && iter->contains(m_NameHead))
        {
            ++iter;
        }
        else
        {
           iter =  listName.erase(iter);
        }
    }

    switch (m_LT)
    {
       case LifeTime_Month:
       {
           timeInt;
        break;
       }
       case LifeTime_Day:
       {

           break;
       }
       case LifeTime_Hour:
       {
          break;
       }
       case LifeTime_Minute:
       {
           break;
       }
       default:
       {
           break;
       }
    }
}


QString QSquallRecorder::GetNameByCurrentTime(void)
{
    QString Name;
    QDateTime dateTime = QDateTime::currentDateTime();

    switch ( m_LT )
    {
    case LifeTime_Forever:
    {
        Name = QString("%1_Only.%2").arg(m_NameHead).arg(m_ExtName);
        break;
    }
    case LifeTime_Month:
    {
        auto &&date = dateTime.date();
        Name = QString("%1_%2%3.%4")
                   .arg(m_NameHead)
                   .arg(date.year())
                   .arg(date.month(),2,10,QChar('0'))
                   .arg(m_ExtName);
        break;
    }
    case LifeTime_Day:
    {
        auto &&date = dateTime.date();
        Name = QString("%1_%2%3%4.%5")
                   .arg(m_NameHead)
                   .arg(date.year())
                   .arg(date.month(),2,10,QChar('0'))
                    .arg(date.day(),2,10,QChar('0'))
                   .arg(m_ExtName);
        break;
    }
    case LifeTime_Hour:
    {
        auto &&date = dateTime.date();
        auto &&time = dateTime.time();
        Name = QString("%1_%2%3%4%5.%6")
                   .arg(m_NameHead)
                   .arg(date.year())
                   .arg(date.month(),2,10,QChar('0'))
                   .arg(date.day(),2,10,QChar('0'))
                   .arg(time.hour(),2,10,QChar('0'))
                   .arg(m_ExtName);
        break;
    }
    case LifeTime_Minute:
    {
        auto &&date = dateTime.date();
        auto &&time = dateTime.time();
        Name = QString("%1_%2%3%4%5%6.%7")
                   .arg(m_NameHead)
                   .arg(date.year())
                   .arg(date.month(),2,10,QChar('0'))
                   .arg(date.day(),2,10,QChar('0'))
                   .arg(time.hour(),2,10,QChar('0'))
                   .arg(time.minute(),2,10,QChar('0'))
                   .arg(m_ExtName);
        break;
    }
    }

    return Name;
}

