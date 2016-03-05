#pragma once

#include <Pdh.h>
#include <list>
#include <string>
#include <numeric>
#include <boost\lexical_cast.hpp>
#include "tool_util.h"
using namespace std;

#pragma comment(lib, "Pdh.lib")

class read_windows_net_log
{
public:
	read_windows_net_log(void);
	~read_windows_net_log(void);

	//return 0 == success, error == -xxxx
	 int get_network_rate(string &ip_rate_, string &down_rate_);

private:
	// 读取网络流量相关
	list<HCOUNTER> m_counters;
	HQUERY m_hQuery;
	string counter_list;
	string instance_list;
	DWORD clistlen ;
	DWORD ilistlen ;
	const char * netface;
	const char * in_speed ;
	const char * out_speed;
	list< double> m_net_total_in_bps;
	list< double> m_net_total_out_bps;
	PDH_STATUS pdhStatus;

	void init();
	//end
};

