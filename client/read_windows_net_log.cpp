#include "read_windows_net_log.h"


read_windows_net_log::read_windows_net_log():clistlen(0),ilistlen(0),netface("Network Interface"),in_speed("Bytes Received/sec"),out_speed("Bytes Sent/sec")
{
	init();
}


read_windows_net_log::~read_windows_net_log(void)
{
}

void read_windows_net_log::init(){
PdhEnumObjectItemsA(0, 0, netface, 0, &clistlen, 0,&ilistlen, PERF_DETAIL_WIZARD, 0);
	counter_list.assign(clistlen, 0);
	instance_list.assign(ilistlen, 0);
	if (ERROR_SUCCESS != PdhEnumObjectItemsA(0, 0, netface, &counter_list[0],&clistlen, &instance_list[0], &ilistlen, PERF_DETAIL_WIZARD, 0))
		return ;
	
	pdhStatus = PdhOpenQuery (0, 0, &m_hQuery);
	if ( pdhStatus != ERROR_SUCCESS )
		return ;
	char *tmpsz = &instance_list[0];
	// 枚举网卡
	for (; *tmpsz!=0; tmpsz+=(strlen(tmpsz)+1))
	{
		string query_obj_in = string("\\") + netface + "(" + tmpsz + ")" + "\\" + in_speed;
		string query_obj_out = string("\\") + netface + "("	+ tmpsz + ")" + "\\" + out_speed;
		HCOUNTER tmpcounter;				
		pdhStatus = PdhAddCounterA( m_hQuery , query_obj_in.c_str(), 0 , &tmpcounter ) ;
		if ( pdhStatus != ERROR_SUCCESS )
		{
			PdhCloseQuery(m_hQuery) ;
			return ;
		}
		m_counters.push_back(tmpcounter);
		pdhStatus = PdhAddCounterA(m_hQuery, query_obj_out.c_str(), 0 , &tmpcounter) ;
		if (pdhStatus != ERROR_SUCCESS)
		{
			PdhCloseQuery (m_hQuery) ;
			return ;
		}
		m_counters.push_back(tmpcounter);
	}
}


int read_windows_net_log::get_network_rate(string &up_rate_, string & down_rate_){

	
	// 统计流量，每秒一次
	PDH_FMT_COUNTERVALUE fmtValue;
	DWORD dwctrType;
	pdhStatus = PdhCollectQueryData(m_hQuery);
	if (pdhStatus != ERROR_SUCCESS)
	{
		return -1;
	}
	double in_bps = 0.0;
	double out_bps = 0.0;
	double in_avg_bps = 0.0;
	double out_avg_bps = 0.0;
	// 遍历每块网卡，把流量加起来
	for (list< HCOUNTER>::iterator iter = m_counters.begin();
		iter != m_counters.end();
		iter++)
	{
		pdhStatus = PdhGetFormattedCounterValue(*iter , PDH_FMT_DOUBLE , 
			&dwctrType , &fmtValue ) ;
		if ( pdhStatus == ERROR_SUCCESS )
		{
			in_bps += fmtValue.doubleValue;
		}
		iter ++;
		pdhStatus = PdhGetFormattedCounterValue(*iter , PDH_FMT_DOUBLE , 
			&dwctrType , &fmtValue ) ;
		if ( pdhStatus == ERROR_SUCCESS )
		{
			out_bps += fmtValue.doubleValue;					
		}
	}
	m_net_total_in_bps.push_back(in_bps);
	m_net_total_out_bps.push_back(out_bps);
	if (m_net_total_in_bps.size() > 10)
		m_net_total_in_bps.pop_front();
	if (m_net_total_out_bps.size() > 10)
		m_net_total_out_bps.pop_front();
	in_avg_bps = accumulate(m_net_total_in_bps.begin(), m_net_total_in_bps.end(),0.0) / m_net_total_in_bps.size();
	out_avg_bps = accumulate(m_net_total_out_bps.begin(), m_net_total_out_bps.end(),0.0) / m_net_total_out_bps.size();

	//保留两位小数
	string in;
	tool_util::leave_two_point(in_avg_bps,in);

	string out;
	tool_util::leave_two_point(out_avg_bps,out);



	up_rate_ = boost::lexical_cast<string>(out) + "KBps";
	down_rate_ = boost::lexical_cast<string>(in) + "KBps";
	return 0;
}