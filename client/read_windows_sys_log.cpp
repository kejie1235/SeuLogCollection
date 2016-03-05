#include "read_windows_sys_log.h"


read_windows_sys_log::read_windows_sys_log(void)
{
}


read_windows_sys_log::~read_windows_sys_log(void)
{
}


int read_windows_sys_log::ReadSystemEventLog(const char *Src, Value &value) 
{
	value["t"] = "win_system_log";
	
	DWORD read_len, next_len; 
	char Buffer[256], Data[4096], *pchar; 
	HANDLE Handle = OpenEventLog(NULL, Src);

	if (Handle==NULL)
	{
		CloseHandle(Handle);
		return -1;
	}
	while(ReadEventLog(Handle, EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ,1, (EVENTLOGRECORD*)Data, sizeof(Data), &read_len, &next_len))
	{
		Value log_object;
		for(short i=0; i<read_len;) 
		{
			//printf("%d\n",read_len);
			EVENTLOGRECORD *ptr = (EVENTLOGRECORD*)(Data+i);
			switch(ptr->EventType) //事件类型  
			{
			case EVENTLOG_SUCCESS:
				pchar= "成功";  
				break; 
			case EVENTLOG_ERROR_TYPE:
				pchar= "错误";
				break; 
			case EVENTLOG_WARNING_TYPE:
				pchar= "警告";
				break; 
			case EVENTLOG_INFORMATION_TYPE:
				pchar= "信息";
				break; 
			case EVENTLOG_AUDIT_SUCCESS:
				pchar= "审计成功";
				break; 
			case EVENTLOG_AUDIT_FAILURE:
				pchar= "审计失败";
				break; 
			default:
				continue; 
			}
			//sprintf(Buffer, "事件\t%u\n", (short)(ptr->EventID)); //事件ID  
			//Result += Buffer;
			log_object["事件"] = boost::lexical_cast<string>(ptr->EventID);

			/*sprintf(Buffer, "类型\t%s\n", pchar); 
			Result += Buffer; */
			log_object["类型"] = boost::lexical_cast<string>(pchar);

			//time_t timep;
			//struct tm *p;
			//time(&timep);
			//p = localtime(&timep);
			//tm *ptm = localtime(&timep);

			tm *ptm = localtime((const time_t *)(&(ptr->TimeWritten)));    //取得当地时间
			sprintf(Buffer, "%.4hd-%.2hd-%.2hd %.2hd:%.2hd:%.2hd",
						ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday,
							ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
			//Result += Buffer;
			log_object["时间"] = Buffer;


			pchar = Data + sizeof(EVENTLOGRECORD); //pchar指向SourceName[]
			//sprintf(Buffer, "来源\t%s\n", pchar); //事件来源 
			//Result += Buffer;
			log_object["来源"] = pchar;


			//pchar += strlen(pchar) + 1; //pchar指向ComputerName[]
			//sprintf(Buffer, "计算机\t%s\n", pchar); //机器名
			//Result += Buffer;
			log_object["计算机"] = pchar;

			pchar += strlen(pchar) + 1;	// pchar指向UserSid
			if(ptr->UserSidLength > 0)
			{
				char Name[64];
				DWORD Length = sizeof(SID), Length1 = sizeof(Buffer);
				SID_NAME_USE Type = SidTypeUser;
				SID *sid = (SID *)(Data + ptr->UserSidOffset);
				if(LookupAccountSid(NULL, sid, Name, &Length, Buffer, &Length1, &Type))
				{
					//查找用户名
					//sprintf(Buffer, "用户\t%s\n", Name); //用户名  
					//Result+=Buffer; 
					log_object["用户"] = Name;

				}
			}
			if(ptr->DataOffset > ptr->StringOffset) //获取事件描述 
			{
				//Result += "[描述]\t"; 
				pchar = Data + i + ptr->StringOffset; 
				for(short j = 0; j < ptr->NumStrings; j++) 
				{
					//Result += pchar; 
					if(j < ptr->NumStrings-1)
						//Result += ' '; 
					pchar += strlen(pchar) + 1;
				} 
				//Result += '\n'; 
				// Result+="[数据]/n"; 
				log_object["[描述]"] = pchar;
			}
			//Result+='\n';
			i+=ptr->Length;
		}

		value["System_log_array"].append(log_object);
	}
	//fwrite(Result.c_str(),Result.length(),1,pFile);
	CloseEventLog(Handle);
	return 0;
}