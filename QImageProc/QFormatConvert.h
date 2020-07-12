#ifndef QFORMATCONVERT_H
#define QFORMATCONVERT_H

#include "CommFile.h"
#include "opencvWindows.h"
#include <vector>
#include <windows.h>

class QFormatConvert
{
public:
    QFormatConvert();

    //载入灰度图片，from Byte* to Mat
    static bool LoadGrayImage(const std::string &PathName, cv::Mat &Matrix);


    //Mat 与 Byte 转换
    static void MonoByteToMat(const BYTE* pImageData, int Width, int Height, cv::Mat &Matrix);
    static void ColorByteToMat(const BYTE* pImageData, int Width, int Height, cv::Mat &Matrix);
    static void MonoMatToByte(const cv::Mat &Matrix, std::vector<BYTE> &vecBuffer);
    static void ColorMatToByte(const cv::Mat &Matrix, std::vector<BYTE> &vecBuffer);


    static bool EncodeToJPEGBuffer(const cv::Mat &Matrix, std::vector<uchar> &JpegBuf);
    static cv::Mat DecodeFromJPEGBuffer(const std::vector<uchar> &JpegBuf);


    static bool TurboJpegEncode(const cv::Mat &Matrix, std::vector<uchar> &JpegBuf);
    //包含比例：1/8, 1/4, 3/8, 1/2, 5/8, 3/4, 7/8, 1/1, 9/8, 5/4, 11/8, 3/2, 13/8, 7/4, 15/8, 2/1
    static cv::Mat TurboJpegDecode(const std::vector<uchar> &JpegBuf, int num = 1, int denom = 1);
};

#endif // QFORMATCONVERT_H
