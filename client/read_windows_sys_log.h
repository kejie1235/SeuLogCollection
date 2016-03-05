#pragma once

#include <windows.h>
#include <string>
#include <time.h>
#include <json\json.h>
#include <boost\lexical_cast.hpp>

using namespace Json;
using namespace std;

class read_windows_sys_log
{
public:
	read_windows_sys_log(void);
	~read_windows_sys_log(void);
	int static ReadSystemEventLog(const char *Src, Value &value );
};

