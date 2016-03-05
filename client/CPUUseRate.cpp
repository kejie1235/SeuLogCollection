#include "CPUUseRate.h"


double CCPUUseRate::FileTimeToDouble(FILETIME &filetime)
{
	return (double)(filetime.dwHighDateTime * 4.294967296E9) + (double)filetime.dwLowDateTime;
}


void CCPUUseRate::GetCPUUseRate(std::string &str)
{
	int nCPUUseRate = 0;
	FILETIME ftIdle, ftKernel, ftUser;
	if (GetSystemTimes(&ftIdle, &ftKernel, &ftUser))
	{
		double fCPUIdleTime = FileTimeToDouble(ftIdle);
		double fCPUKernelTime = FileTimeToDouble(ftKernel);
		double fCPUUserTime = FileTimeToDouble(ftUser);
		nCPUUseRate= (int)(100.0 - (fCPUIdleTime - m_fOldCPUIdleTime) 
			/ (fCPUKernelTime - m_fOldCPUKernelTime + fCPUUserTime - m_fOldCPUUserTime) 
			*100.0);
		m_fOldCPUIdleTime = fCPUIdleTime;
		m_fOldCPUKernelTime = fCPUKernelTime;
		m_fOldCPUUserTime = fCPUUserTime;
	}
	tool_util::leave_two_point(nCPUUseRate,str);
}

BOOL CCPUUseRate::Initialize() 
{
	FILETIME ftIdle, ftKernel, ftUser;
	BOOL flag = FALSE;
	if (flag = GetSystemTimes(&ftIdle, &ftKernel, &ftUser))
	{
		m_fOldCPUIdleTime = FileTimeToDouble(ftIdle);
		m_fOldCPUKernelTime = FileTimeToDouble(ftKernel);
		m_fOldCPUUserTime = FileTimeToDouble(ftUser);

	}
	return flag;
}