#include "NovieSimpleImageWidget.h"
#include <QPainter>
#include <QWheelEvent>
#include <QTimer>

QNovieSimpleImageWidget::QNovieSimpleImageWidget(QWidget* parent)
    : QWidget(parent)
    , m_SrcStart(QPoint(0,0))
    , m_IsMouseTrack(false)
{
    m_IsMovingPhoto = false;
    m_Scale = 1.0f;
    setMouseTracking(true);
}
QNovieSimpleImageWidget::~QNovieSimpleImageWidget()
{

}

//最佳比例加载
bool QNovieSimpleImageWidget::LoadPhotoAtBestScale(const uchar* pImage, int width, int height, int channels)
{
    if (LoadImage(pImage, width,height, channels))
    {
        SetBestScale();

        update();
        return true;
    }

    LoadEmptyPhoto();
    return false;
}

bool QNovieSimpleImageWidget::LoadPhotoAtBestScale(uchar* pImage, int width, int height, int channels)
{
  return LoadPhotoAtBestScale((const uchar*)pImage, width, height, channels);
}

bool QNovieSimpleImageWidget::LoadPhotoAtBestScale(char* pImage, int width, int height, int channels)
{
   return LoadPhotoAtBestScale((const uchar*)pImage, width, height, channels);
}

bool QNovieSimpleImageWidget::LoadPhotoAtBestScale(const char* pImage, int width, int height, int channels)
{
  return LoadPhotoAtBestScale((const uchar*)pImage, width, height, channels);
}

bool QNovieSimpleImageWidget::LoadPhotoAtBestScale(const std::string& path)
{
    if (LoadImage(path))
    {
        SetBestScale();

        update();
        return true;
    }
    LoadEmptyPhoto();
    return false;
}

bool QNovieSimpleImageWidget::LoadPhotoAtBestScale(const QImage& Image)
{
    if (LoadImage(Image))
    {
        SetBestScale();

        update();
        return true;
    }
    LoadEmptyPhoto();
    return false;
}


// 保留原始比例加载图片，常用作查看相机采集
bool QNovieSimpleImageWidget::LoadPhotoAtOldScale(const uchar* pImage, int width, int height, int channels)
{
    if (LoadImage(pImage, width, height, channels))
    {
        update();
        return true;
    }
    LoadEmptyPhoto();
    return false;
}

bool QNovieSimpleImageWidget::LoadPhotoAtOldScale(uchar* pImage, int width, int height, int channels)
{
    return LoadPhotoAtOldScale((const uchar*)pImage, width, height, channels);
}

bool QNovieSimpleImageWidget::LoadPhotoAtOldScale(char* pImage, int width, int height, int channels)
{
    return LoadPhotoAtOldScale((const uchar*)pImage, width, height, channels);
}

bool QNovieSimpleImageWidget::LoadPhotoAtOldScale(const char* pImage, int width, int height, int channels)
{
   return LoadPhotoAtOldScale((const uchar*)pImage, width, height, channels);
}

bool QNovieSimpleImageWidget::LoadPhotoAtOldScale(const std::string& path)
{
    if (LoadImage(path))
    {
        update();
        return true;
    }
    LoadEmptyPhoto();
    return false;
}

bool QNovieSimpleImageWidget::LoadPhotoAtOldScale(const QImage& Image)
{
    if (LoadImage(Image))
    {
        update();
        return true;
    }
    LoadEmptyPhoto();
    return false;
}


void QNovieSimpleImageWidget::LoadEmptyPhoto()
{
    if (!m_Image.isNull())
    {
        m_Image = QImage();
    }
    update();
}


QImage QNovieSimpleImageWidget::GetWndQImage()const
{
    if (m_Image.isNull()) return QImage();

    return QImage(m_Image);
}


void QNovieSimpleImageWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(192, 192, 192), 2));
    painter.setBrush(QColor(192, 192, 192));
    painter.drawRect(0, 0, width(), height());
    if (!m_Image.isNull())
    {
        int Width = int(width() * m_Scale);
        int Height = int(height() * m_Scale);
        painter.drawImage(rect(), m_Image, QRect(m_SrcStart.x(), m_SrcStart.y(), Width, Height));
    }
    else
    {
        painter.save();
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QColor(0, 0, 0));

        QFont font;
        font.setFamily("Microsoft YaHei");
        font.setPointSize(50);
        font.setItalic(true);
        painter.setFont(font);

        painter.drawText(rect(), Qt::AlignCenter, QString::fromLocal8Bit("No Image"));
        painter.restore();
    }
}

void QNovieSimpleImageWidget::wheelEvent(QWheelEvent* event)
{
    if (m_Image.isNull()) return;
    auto ClientPt = event->pos();
    auto ImagePt = Client2Image(ClientPt);

    if (!m_Image.valid(ImagePt)) return;

    float Scale = ScaleStrategy(event->delta() > 0 ? true : false);
    SetScale(Scale);
    SetImageClient(ImagePt, ClientPt);
    AutoAdjust();
    update();
}


void QNovieSimpleImageWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (m_Image.isNull())
    {
        setCursor(Qt::ArrowCursor);
        return;
    }


    auto ClientPoint = event->pos();

    // 鼠标在图像中坐标
    auto ImagePoint = Client2Image(event->pos());

    //移动图
    if (m_IsMovingPhoto)  //移动
    {
        setCursor(Qt::ClosedHandCursor);

        auto offsetX = ClientPoint.x() - m_OldPoint.x();
        auto offsetY = ClientPoint.y() - m_OldPoint.y();
        m_SrcStart.setX(static_cast<int>(m_OldSrcStart.x() - offsetX*m_Scale));
        m_SrcStart.setY(static_cast<int>(m_OldSrcStart.y() - offsetY*m_Scale));
        AutoAdjust();

    }
    update();
}

void QNovieSimpleImageWidget::mousePressEvent(QMouseEvent* event)
{
    if (!m_Image.isNull() && m_Image.valid(Client2Image(event->pos())))
    {
        if (Qt::LeftButton == event->button())
        {
            setCursor(Qt::ClosedHandCursor);
            m_IsMovingPhoto = true;
            m_OldSrcStart = m_SrcStart;
            m_OldPoint = event->pos();
        }
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}

void QNovieSimpleImageWidget::mouseReleaseEvent(QMouseEvent* event)
{
    setCursor(Qt::ArrowCursor);
    m_IsMovingPhoto = false;
}


void QNovieSimpleImageWidget::resizeEvent(QResizeEvent* event)
{

}


void QNovieSimpleImageWidget::enterEvent(QEvent* event)
{
    m_IsMouseTrack = true;
   // update();
}

void QNovieSimpleImageWidget::leaveEvent(QEvent* event)
{
    m_IsMouseTrack = false;
    //update();
}



void  QNovieSimpleImageWidget::SetScale(float Scale)
{
   m_Scale = Scale;
}

float QNovieSimpleImageWidget::GetScale() const
{
   return m_Scale;
}


float QNovieSimpleImageWidget::GetBestScale()
{
    float scaleWidth = float(m_Image.width()) / width();
    float scaleHeight = float(m_Image.height()) / height();
    float scaleMax = 0, scale = 1;

    if (scaleWidth >= scaleHeight)
    {
        scaleMax = scaleWidth;
    }
    else
    {
        scaleMax = scaleHeight;
    }

    if (scaleMax > 1)
    {
        scale = scaleMax;
    }

    return scale;
}

void  QNovieSimpleImageWidget::SetBestScale()
{
    float Scale = GetBestScale();
    SetScale(Scale);
    SetClientCenterPoint(QPoint(m_Image.width() / 2, m_Image.height() / 2));
}


QPoint QNovieSimpleImageWidget::Client2Image(QPoint pt)  //窗口坐标到图坐标，注意算出的点有可以不再图像上
{
    QPoint ImagePt;
    ImagePt.setX(m_SrcStart.x() + int(pt.x()* m_Scale));
    ImagePt.setY(m_SrcStart.y() + int(pt.y()* m_Scale));
    return ImagePt;
}

QPoint QNovieSimpleImageWidget::Image2Client(QPoint pt) // 图像到窗口坐标
{
    QPoint ClientPt;
    ClientPt.setX((pt.x() - m_SrcStart.x()) / m_Scale);
    ClientPt.setY((pt.y() - m_SrcStart.y()) / m_Scale);
    return ClientPt;
}


void  QNovieSimpleImageWidget::AutoAdjust()        // 调节图像拷贝点
{
    Q_ASSERT(!m_Image.isNull());

    //当缩放越界时，进行自动调整
    long ViewWidth = long(width() * m_Scale);
    long ViewHeight = long(height() * m_Scale);

    if (m_SrcStart.x() < 0)
        m_SrcStart.setX(0) ;
    if (m_SrcStart.x() > m_Image.width() - width() * m_Scale)
        m_SrcStart.setX( long(m_Image.width() - width() * m_Scale));
    if (ViewWidth > m_Image.width())
        m_SrcStart.setX((m_Image.width() - ViewWidth) / 2);

    if (m_SrcStart.y() < 0)
        m_SrcStart.setY(0);
    if (m_SrcStart.y() > m_Image.height() - height() * m_Scale)
        m_SrcStart.setY(long(m_Image.height() - height() * m_Scale));
    if (ViewHeight > m_Image.height())
        m_SrcStart.setY((m_Image.height() - ViewHeight) / 2);
}

float  QNovieSimpleImageWidget::ScaleStrategy(bool bScaleUp)
{
    static const float a[] = {0.02f,0.04f, 0.08f, 0.10f,0.125f, 0.25f, 0.375f, 0.5f, 0.625f, 0.75f, 0.875f, 1.0f,
                              1.2f, 1.4f, 1.6f, 1.8f, 2.0f, 2.2f, 2.4f, 2.6f, 2.8f, 3.0f,
                              3.3f, 3.6f, 3.9f, 4.2f, 4.6f, 5.0f, 5.5f, 6.0f,
                              7.0f, 8.0f, 9.0f, 10.0f, 12.0f, 14.0f, 16.0f};

    float fRet = -1;
    int count = sizeof(a) / sizeof(float);
    if (bScaleUp)
    {
        for (int i = count - 1; i > 0; i--)
        {
            if (m_Scale == a[i])
            {
                if (i > 0)
                {
                    fRet = a[i - 1];
                }
                else
                {
                    fRet = m_Scale;
                }

                break;
            }
            else if (m_Scale > a[i])
            {
                fRet = a[i];

                break;
            }
        }

        if (fRet == -1)
        {
            fRet = a[0];
        }
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            if (m_Scale == a[i])
            {
                if (i < count - 1)
                {
                    fRet = a[i + 1];
                }
                else
                {
                    fRet = m_Scale;
                }

                break;
            }
            else if (m_Scale < a[i])
            {
                fRet = a[i];

                break;
            }
        }

        if (fRet == -1)
        {
            fRet = a[count - 1];
        }
    }

    return fRet;
}


void  QNovieSimpleImageWidget::SetImageClient(QPoint ImagePt,QPoint ClientPt) // 使图像上的点在窗口的某个点上
{
    m_SrcStart.setX(ImagePt.x() - int(m_Scale*ClientPt.x()));
    m_SrcStart.setY(ImagePt.y() - int(m_Scale*ClientPt.y()));
}

void   QNovieSimpleImageWidget::SetClientCenterPoint(QPoint pt) // 设置窗口的正中央为图像的某个点
{
    m_SrcStart.setX(pt.x() - m_Scale * width() / 2);
    m_SrcStart.setY(pt.y() - m_Scale * height() / 2);
}

QPoint QNovieSimpleImageWidget::GetClientCenterPoint()  // 查看窗口的正中央为图像的某个点
{
    QPoint pt;
    pt.setX(m_SrcStart.x() + m_Scale * width() / 2);
    pt.setY(m_SrcStart.y() + m_Scale * height() / 2);
    return pt;
}


bool  QNovieSimpleImageWidget::LoadImage(const uchar* pImage, int width, int height, int channels)
{
    Q_ASSERT(pImage != nullptr);
    Q_ASSERT(channels == 1 || channels == 3);
    auto Format = channels == 1 ? QImage::Format::Format_Grayscale8 : QImage::Format::Format_RGB888;
    m_Image = QImage(width, height, Format);

    if (m_Image.isNull()) return false;

    for (int i = 0; i < m_Image.height(); ++i)
    {
        memcpy(m_Image.scanLine(i), pImage + width * i *channels, width * channels);
    }
    return true;
}

bool  QNovieSimpleImageWidget::LoadImage(const std::string& path)
{
    m_Image.load(QString::fromLocal8Bit(path.data()));
    if (m_Image.isNull()) return false;
    return true;
}

bool  QNovieSimpleImageWidget::LoadImage(const QImage& Image)
{
    if (Image.isNull()) return false;
    m_Image = Image;

    if (m_Image.isNull()) return false;
    return true;
}

