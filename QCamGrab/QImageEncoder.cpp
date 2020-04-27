#include "QImageEncoder.h"


#include <QString>
#include "QFileData.h"
#include <QFile>
#include <iostream>


namespace Frederic
{
   struct bmpFileHead  // 14
   {
       bmpFileHead(int w,int h,int channels,int depth = 8)
       {
           Q_ASSERT(depth == 8);
           Q_ASSERT(channels == 1|| channels == 3);
           bfType = 0x4d42;

           int size = 54 + (channels == 1?4*256:0) +((w*channels+ 3)/4)*4*h;
           memcpy(&bfSize0,&size,4);

           bfReserved1 = 0;
           bfReserved2 = 0;

           uint  bfOffBits = 54 + (channels==1?4*256:0);
           memcpy(&bfOffBits1,&bfOffBits,4);
       }
       short    bfType;
       short    bfSize0;
       short    bfSize1;
       short    bfReserved1;
       short    bfReserved2;
       short    bfOffBits1;
       short    bfOffBits2;
   };

   struct bmpInfoHead  //40
   {
       bmpInfoHead(int w,int h,int channels,int depth = 8)
       {
           Q_ASSERT(depth == 8);
           Q_ASSERT(channels == 1|| channels == 3);
           biSize = 40;
           biWidth = w;
           biHeight = -h;  // Action
           biPlanes = 1;
           biBitCount = depth;
           biCompression = 0;
           biSizeImage = 0;
           biXPelsPerMeter = 0;
           biYPelsPerMeter = 0;
           biClrUsed = channels == 1 ? 0 : 0;
           biClrImportant = channels == 1 ? 0 : 0;
       }
       int         biSize;
       int         biWidth;
       int         biHeight;
       short       biPlanes;
       short       biBitCount;
       int         biCompression;
       int         biSizeImage;
       int         biXPelsPerMeter;
       int         biYPelsPerMeter;
       int         biClrUsed;
       int         biClrImportant;
   };

   typedef struct tagRGBQUAD
   {
     uchar    rgbBlue;
     uchar    rgbGreen;
     uchar    rgbRed;
     uchar    rgbReserved;
    } RGBQUAD;
   struct Palette  //256*4 1024
   {
       Palette()
       {
           for(int i =0;i<256;++i)
           {
               color[i].rgbBlue=i;
               color[i].rgbGreen=i;
               color[i].rgbRed=i;
               color[i].rgbReserved=0;
           }
       }
       tagRGBQUAD color[256];
   };
};

QImageEncoder::QImageEncoder()
{

}

QImageEncoder::~QImageEncoder()
{

}


 bool QImageEncoder::saveBMP(const QString &path,unsigned char *pData,int width,int height,int channels)
 {
     Q_ASSERT(pData&&width>0&&height>0);
     Q_ASSERT(channels == 1 || channels == 3);

     if (path.isEmpty()) return false;

     // 转 反斜杠(\\)为斜杠(/)
     QString FileName =  Frederic::QFileData::TransSlash(path);

     QFile File(FileName);
     if (File.exists())
     {
         File.remove();
     }

     if (File.open(QIODevice::WriteOnly | QIODevice::Append))
     {
         Frederic::bmpFileHead hd(width,height,channels);
         Frederic::bmpInfoHead info(width,height,channels);
         Frederic::Palette patte;
         File.write((const char*)(&hd),sizeof(hd));
         File.write((const char*)(&info),sizeof(info));

         if(channels==1)
         {
            File.write((const char*)(&patte),sizeof(patte));
         }

         if((channels*width) % 4 !=0)
         {
             int buffersize = 4 - ((channels*width) % 4);
             auto p = new char[buffersize];
             memset(p,0,buffersize);

             for(int i = 0; i < height; ++i)
             {
                 File.write((const char*)(pData + channels * width * i),width*channels);
                 File.write(p,buffersize);
             }

             delete []p;
         }
         else
         {
              File.write((const char*)(pData),width*height);
         }


         File.close();
     }

     return true;
 }

bool QImageEncoder::savePNG(const QString &path,uchar *pData,int width,int height,int channels,int quality)
{
    Q_ASSERT(pData&&width>0&&height>0);
    Q_ASSERT(channels == 1 || channels == 3);

    //novice::QFileData::WriteData(path,pData,width*height);

    return true;
}

bool QImageEncoder::saveJPG(const QString &path,uchar *pData,int width,int height,int channels,int quality)
{
    Q_ASSERT(pData&&width>0&&height>0);
    Q_ASSERT(channels == 1 || channels == 3);
    return false;
}
