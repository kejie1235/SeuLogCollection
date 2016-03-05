#include "memory_hdd.h"


memory_hdd::memory_hdd(void)
{
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx (&statex);
}


memory_hdd::~memory_hdd(void)
{

}


void memory_hdd::get_total_memory(std::string &str){
	unsigned long long t = statex.ullTotalPhys/DIV;
	double d = t/DIV;
	d = d/DIV;
	
	tool_util::leave_two_point(d,str);
	str +='G';
}

void memory_hdd::get_use_memory(std::string &str){
	tool_util::leave_two_point(statex.dwMemoryLoad);
	str +='G';
}

void memory_hdd::get_free_memory(std::string &str){
	unsigned long long t = statex.ullAvailPhys/DIV;
	double d = t/DIV;
	d = d/DIV;

	tool_util::leave_two_point(d,str);
	str +='G';
}