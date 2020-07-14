#ifndef QNOVIESIMPLEIMAGEWIDGET_H
#define QNOVIESIMPLEIMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include <QString>

class QNovieSimpleImageWidget : public QWidget
{
public:
    explicit QNovieSimpleImageWidget(QWidget* parent = nullptr);
    ~QNovieSimpleImageWidget();

    //最佳比例加载
    bool LoadPhotoAtBestScale(const uchar* pImage, int width, int height, int channels);
    bool LoadPhotoAtBestScale(uchar* pImage, int width, int height, int channels);
    bool LoadPhotoAtBestScale(char* pImage, int width, int height, int channels);
    bool LoadPhotoAtBestScale(const char* pImage, int width, int height, int channels);
    bool LoadPhotoAtBestScale(const std::string& path);
    bool LoadPhotoAtBestScale(const QImage& Image);

    // 保留原始比例加载图片，常用作查看相机采集
    bool LoadPhotoAtOldScale(const uchar* pImage, int width, int height, int channels);
    bool LoadPhotoAtOldScale(uchar* pImage, int width, int height, int channels);
    bool LoadPhotoAtOldScale(char* pImage, int width, int height, int channels);
    bool LoadPhotoAtOldScale(const char* pImage, int width, int height, int channels);
    bool LoadPhotoAtOldScale(const std::string& path);

    bool LoadPhotoAtOldScale(const QImage& Image);

    void LoadEmptyPhoto();

    QImage GetWndQImage()const;

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent* event) Q_DECL_OVERRIDE;

    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

    void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;

    void enterEvent(QEvent* event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent* event) Q_DECL_OVERRIDE;

public:
    float GetScale() const;
protected:
    void  SetScale(float Scale);

    float GetBestScale();
    void  SetBestScale();

    QPoint Client2Image(QPoint pt);  //窗口坐标到图坐标，注意算出的点有可以不再图像上
    QPoint Image2Client(QPoint pt); // 图像到窗口坐标

    void   AutoAdjust();        // 调节图像拷贝点
    float  ScaleStrategy(bool bScaleUp = true);

    void  SetImageClient(QPoint ImagePt,QPoint ClientPt); // 使图像上的点在窗口的某个点上

    void   SetClientCenterPoint(QPoint pt); // 设置窗口的正中央为图像的某个点
    QPoint GetClientCenterPoint(); // 查看窗口的正中央为图像的某个点


    bool   LoadImage(const uchar* pImage, int width, int height, int channels);
    bool   LoadImage(const std::string& path);
    bool   LoadImage(const QImage& Image);

protected:
    QImage  m_Image;
    float   m_Scale;  //比例，比例越大，放的越小

    QPoint  m_SrcStart; // 图像的拷贝点

    bool   m_IsMovingPhoto;
    QPoint m_OldSrcStart;		//记录旧的原图拷贝起始点
    QPoint m_OldPoint;			//旧的鼠标位置

    bool      m_IsMouseTrack;   // 鼠标移进出
};

#endif // QNOVIESIMPLEIMAGEWIDGET_H
