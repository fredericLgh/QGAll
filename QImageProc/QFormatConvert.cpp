#include "QFormatConvert.h"

using namespace cv;

QFormatConvert::QFormatConvert()
{

}

bool QFormatConvert::LoadGrayImage(const std::string &PathName, cv::Mat &Matrix)
{
    return true;
}

//Mat 与 Byte 转换
void QFormatConvert::MonoByteToMat(const BYTE* pImageData, int Width, int Height, cv::Mat &Matrix)
{
    ENSURE_EXPRESSION(pImageData != nullptr);
    ENSURE_EXPRESSION(Width > 0 && Height > 0);

    Matrix.create(cv::Size(Width, Height), CV_8UC1);

    if (Matrix.isContinuous())
    {
        memcpy(Matrix.data, pImageData, Height * Width);
    }
    else
    {
        for (int i = 0; i < Height; i++)
        {
            uchar* p = Matrix.ptr<uchar>(i);
            BYTE* srcp = (BYTE*)pImageData + i * Width;

            memcpy(p, srcp, Width);
        }
    }
}

void QFormatConvert::ColorByteToMat(const BYTE* pImageData, int Width, int Height, cv::Mat &Matrix)
{
    ENSURE_EXPRESSION(pImageData != nullptr);
    ENSURE_EXPRESSION(Width > 0 && Height > 0);

    Matrix.create(cv::Size(Width, Height), CV_8UC3);

    if (Matrix.isContinuous())
    {
        memcpy(Matrix.data, pImageData, Height * Width * 3);
    }
    else
    {
        for (int i = 0; i < Height; i++)
        {
            uchar* p = Matrix.ptr<uchar>(i);
            BYTE* srcp = (BYTE*)pImageData + i * Width * 3;

            memcpy(p, srcp, Width * 3);
        }
    }
}

void QFormatConvert::MonoMatToByte(const cv::Mat &Matrix, std::vector<BYTE> &vecBuffer)
{
    ENSURE_EXPRESSION(!Matrix.empty());

    vecBuffer.resize(Matrix.cols * Matrix.rows);

    if (Matrix.isContinuous())
    {
        memcpy(&vecBuffer[0], Matrix.data, Matrix.cols * Matrix.rows);
    }
    else
    {
        for (int i = 0; i < Matrix.rows; i++)
        {
            const uchar* pSrc = Matrix.ptr<uchar>(i);
            BYTE* pDst = &vecBuffer[0] + i * Matrix.cols;
            memcpy(pDst, pSrc, Matrix.cols);
        }
    }
}

void QFormatConvert::ColorMatToByte(const cv::Mat &Matrix, std::vector<BYTE> &vecBuffer)
{
    ENSURE_EXPRESSION(!Matrix.empty());
    ENSURE_EXPRESSION(Matrix.type() == CV_8UC3);

    vecBuffer.resize(Matrix.cols * Matrix.rows * 3);

    if (Matrix.isContinuous())
    {
        memcpy(&vecBuffer[0], Matrix.data, Matrix.cols * Matrix.rows * 3);
    }
    else
    {
        for (int i = 0; i < Matrix.rows; i++)
        {
            const uchar* pSrc = Matrix.ptr<uchar>(i);
            BYTE* pDst = &vecBuffer[0] + i * Matrix.cols * 3;
            memcpy(pDst, pSrc, Matrix.cols * 3);
        }
    }
}



bool QFormatConvert::EncodeToJPEGBuffer(const cv::Mat &Matrix, std::vector<uchar> &JpegBuf)
{
    return true;
}

cv::Mat QFormatConvert::DecodeFromJPEGBuffer(const std::vector<uchar> &JpegBuf)
{
    return cv::Mat();
}



bool QFormatConvert::TurboJpegEncode(const cv::Mat &Matrix, std::vector<uchar> &JpegBuf)
{
    std::vector<int> param = std::vector<int>(2);
    param[0] = cv::ImwriteFlags::IMWRITE_JPEG_QUALITY;	
    param[1] = 95; // default(95) 0-100
    bool b = cv::imencode(".jpg",Matrix,JpegBuf,param);
    return b;
}

//包含比例：1/8, 1/4, 3/8, 1/2, 5/8, 3/4, 7/8, 1/1, 9/8, 5/4, 11/8, 3/2, 13/8, 7/4, 15/8, 2/1
cv::Mat QFormatConvert::TurboJpegDecode(const std::vector<uchar> &JpegBuf, int num, int denom)
{
    return cv::Mat();
}

