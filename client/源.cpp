#include "read_windows_sys_log.h"
#include "read_windows_net_log.h"
#include "CPUUseRate.h"
#include "memory_hdd.h"
#include <iostream>



int main(){
	//测试json用例
	//Value value;
	//read_windows_sys_log::ReadSystemEventLog("System",value);
	//std::cout<<value.toStyledString()<<"\n";
	
	//测试网络速率用例
	/*read_windows_net_log host_log;
	while(1){
	string in;
	string out;
	
	int flag = host_log.get_network_rate(in, out);
	assert(flag == 0);

	std::cout<<"up: "<<in<<"\t"<<"down: "<<out<<"\n";
	Sleep(1000);
	}*/

	//测试cpu用例
	/*CCPUUseRate cpuUseRate;
	if (!cpuUseRate.Initialize())
	{
		printf("Error! %d\n", GetLastError());
		return -1;
	}
	else
	{
		while (true)
		{	
			Sleep(1000);
			printf("\r当前CPU使用率为：%d%%", cpuUseRate.GetCPUUseRate());
		}
	}*/

	//内存使用用例
	memory_hdd mem_hdd;
	cout<<"总内存："<<mem_hdd.get_total_memory()<<"\n"<<"G";
	cout<<"内存使用率："<<mem_hdd.get_use_memory()<<"\n";
	cout<<"未使用内存："<<mem_hdd.get_free_memory()<<"\n"<<"G";

	system("pause");

}

