// ���ϵͳCPUʹ����
// http://blog.csdn.net/morewindows/article/details/8678359
// By MoreWindows( http://blog.csdn.net/MoreWindows )
// �ȵ���Initialize()��Ȼ��while(true){Sleep(1000);GetCPUUseRate();}���ܻ��CPUʹ���ʡ�
// �������ԣ�������WinXP��Win7��ʹ�á�
#pragma once

#include <Windows.h>
#include <string>
#include "tool_util.h"

class CCPUUseRate
{
public:
	//����Initialize��Ҫ�ȴ�1���ٵ��ô˺���
	BOOL Initialize() ;	
	void GetCPUUseRate(std::string &str);
private:
	double FileTimeToDouble(FILETIME &filetime);
private:
	double m_fOldCPUIdleTime;
	double m_fOldCPUKernelTime;
	double m_fOldCPUUserTime;
};
