// 获得系统CPU使用率
// http://blog.csdn.net/morewindows/article/details/8678359
// By MoreWindows( http://blog.csdn.net/MoreWindows )
// 先调用Initialize()，然后while(true){Sleep(1000);GetCPUUseRate();}就能获得CPU使用率。
// 经过测试，可以在WinXP及Win7下使用。
#pragma once

#include <Windows.h>
#include <string>
#include "tool_util.h"

class CCPUUseRate
{
public:
	//调用Initialize后要等待1秒再调用此函数
	BOOL Initialize() ;	
	void GetCPUUseRate(std::string &str);
private:
	double FileTimeToDouble(FILETIME &filetime);
private:
	double m_fOldCPUIdleTime;
	double m_fOldCPUKernelTime;
	double m_fOldCPUUserTime;
};
