#pragma once


#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include "tool_util.h"

#define DIV 1024;
class memory_hdd
{
public:
	memory_hdd(void);
	~memory_hdd(void);

	void get_total_memory(std::string &str);
	void get_use_memory(std::string &str);
	void get_free_memory(std::string &str);

private:
	  MEMORYSTATUSEX statex;



};

