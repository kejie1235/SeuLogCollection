#include "read_windows_sys_log.h"
#include "read_windows_net_log.h"
#include "CPUUseRate.h"
#include "memory_hdd.h"
#include <iostream>



int main(){
	//����json����
	//Value value;
	//read_windows_sys_log::ReadSystemEventLog("System",value);
	//std::cout<<value.toStyledString()<<"\n";
	
	//����������������
	/*read_windows_net_log host_log;
	while(1){
	string in;
	string out;
	
	int flag = host_log.get_network_rate(in, out);
	assert(flag == 0);

	std::cout<<"up: "<<in<<"\t"<<"down: "<<out<<"\n";
	Sleep(1000);
	}*/

	//����cpu����
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
			printf("\r��ǰCPUʹ����Ϊ��%d%%", cpuUseRate.GetCPUUseRate());
		}
	}*/

	//�ڴ�ʹ������
	memory_hdd mem_hdd;
	cout<<"���ڴ棺"<<mem_hdd.get_total_memory()<<"\n"<<"G";
	cout<<"�ڴ�ʹ���ʣ�"<<mem_hdd.get_use_memory()<<"\n";
	cout<<"δʹ���ڴ棺"<<mem_hdd.get_free_memory()<<"\n"<<"G";

	system("pause");

}

