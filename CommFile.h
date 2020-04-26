#pragma once

#ifndef COMMFILE_H
#define COMMFILE_H

typedef unsigned int UINT ;
typedef int BOOL;
typedef unsigned char BYTE, *LPBYTE;
typedef unsigned char uchar;

typedef  unsigned short WORD;
typedef  unsigned long DWORD;

typedef unsigned long ULONG;

typedef void* LPVOID;


typedef struct _SYSTEMTIME {
    WORD wYear;//年
    WORD wMonth;//月
    WORD wDayOfWeek;//星期
    WORD wDay;//日
    WORD wHour;//时
    WORD wMinute;//分
    WORD wSecond;//秒
    WORD wMilliseconds;//毫秒
} SYSTEMTIME;


//*************************** 异常处理宏定义 (by Squall) ******************************
#include <exception>
#include <sstream>
#include <memory>
#include <string>
#include <stdio.h>
#include <stdexcept>


inline std::shared_ptr<std::string> Ensure_Detail1(const char* pstr, const char* pFuncName, int nLineNum )
{
    std::stringstream ss;
    ss << "\r\nENSURE_EXPRESSION 失败：\r\n  " << pstr ;
    ss << "\r\n函数名称：\r\n  " << pFuncName ;
    ss << "\r\n错误行号：\r\n  " << nLineNum ;

    return std::make_shared<std::string>(ss.str());
}

#ifdef WIN
#define ENSURE_EXPRESSION(b) if(!(b))\
 throw std::exception(std::logic_error(Ensure_Detail1(#b,__FILE__,__LINE__)->c_str()))
#elif __linux__
  #define ENSURE_EXPRESSION(b) if(!(b))\
 throw std::exception(std::logic_error(Ensure_Detail1(#b,__FILE__,__LINE__)->c_str()))
#endif


#endif // LINUXCOMMFILE_H
