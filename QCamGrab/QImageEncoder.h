#ifndef QIMAGEENCODER_H
#define QIMAGEENCODER_H

class QString;

class QImageEncoder
{
public:
    explicit QImageEncoder();
    ~QImageEncoder();

    bool saveBMP(const QString &path,unsigned char *pData,int width,int height,int channels = 1);
    bool savePNG(const QString &path,unsigned char *pData,int width,int height,int channels = 1,int quality = -1);
    bool saveJPG(const QString &path,unsigned char *pData,int width,int height,int channels = 1,int quality = -1);

};

#endif // QIMAGEENCODER_H
