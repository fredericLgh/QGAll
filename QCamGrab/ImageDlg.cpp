#include "ImageDlg.h"
#include "NovieSimpleImageWidget.h"
#include <QResizeEvent>
#include <QTimer>
#include <QString>
#include "QCameraApp.h"
#include <QGuiApplication>
#include <QScreen>


QImageDlg::QImageDlg(QWidget *parent)
          : QWidget(parent)
          , m_pImageWidget(nullptr)
          , m_pTimer(nullptr)
{
    InitWnd();
}

QImageDlg::~QImageDlg()
{
    ExitWnd();
}

void QImageDlg::InitWnd()
{
    setWindowTitle(QString::fromLocal8Bit("影像"));

    setGeometry(QApplication::primaryScreen()->availableVirtualGeometry());

    m_pTimer = new QTimer(this);
    connect(m_pTimer,&QTimer::timeout,this,&QImageDlg::TimeOut);
    m_pTimer->start(100);
}

void QImageDlg::ExitWnd()
{

}

void QImageDlg::TimeOut()
{
    static bool isFirstOpen = true;
    static long OldInx = IMAGE_ARRAY_SIZE - 1;

    StructRawImage* pImage;
    long nIndex;
    pApp->g_mem.ReadRawData(pImage, nIndex);

    if (nIndex != OldInx && m_pImageWidget)
    {
        if(!isFirstOpen)
        {
           m_pImageWidget->LoadPhotoAtOldScale(pImage->RawImageBuf,pApp->m_ImageWidth,  pApp->m_ImageHeight,1);
        }
        else
        {
           isFirstOpen =false;
           m_pImageWidget->LoadPhotoAtBestScale(pImage->RawImageBuf,pApp->m_ImageWidth,  pApp->m_ImageHeight,1);
        }

        setWindowTitle(QString::fromLocal8Bit("影像 ( %1 x )").arg(m_pImageWidget->GetScale()));
        OldInx = nIndex;
    }
}

void QImageDlg::resizeEvent(QResizeEvent *event)
{
    if(!m_pImageWidget)
    {
        m_pImageWidget = new QNovieSimpleImageWidget(this);
    }

    m_pImageWidget->setFixedSize(this->size());
    m_pImageWidget->move(0,0);

    QWidget::resizeEvent(event);
}
