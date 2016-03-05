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
			switch(ptr->EventType) //�¼�����  
			{
			case EVENTLOG_SUCCESS:
				pchar= "�ɹ�";  
				break; 
			case EVENTLOG_ERROR_TYPE:
				pchar= "����";
				break; 
			case EVENTLOG_WARNING_TYPE:
				pchar= "����";
				break; 
			case EVENTLOG_INFORMATION_TYPE:
				pchar= "��Ϣ";
				break; 
			case EVENTLOG_AUDIT_SUCCESS:
				pchar= "��Ƴɹ�";
				break; 
			case EVENTLOG_AUDIT_FAILURE:
				pchar= "���ʧ��";
				break; 
			default:
				continue; 
			}
			//sprintf(Buffer, "�¼�\t%u\n", (short)(ptr->EventID)); //�¼�ID  
			//Result += Buffer;
			log_object["�¼�"] = boost::lexical_cast<string>(ptr->EventID);

			/*sprintf(Buffer, "����\t%s\n", pchar); 
			Result += Buffer; */
			log_object["����"] = boost::lexical_cast<string>(pchar);

			//time_t timep;
			//struct tm *p;
			//time(&timep);
			//p = localtime(&timep);
			//tm *ptm = localtime(&timep);

			tm *ptm = localtime((const time_t *)(&(ptr->TimeWritten)));    //ȡ�õ���ʱ��
			sprintf(Buffer, "%.4hd-%.2hd-%.2hd %.2hd:%.2hd:%.2hd",
						ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday,
							ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
			//Result += Buffer;
			log_object["ʱ��"] = Buffer;


			pchar = Data + sizeof(EVENTLOGRECORD); //pcharָ��SourceName[]
			//sprintf(Buffer, "��Դ\t%s\n", pchar); //�¼���Դ 
			//Result += Buffer;
			log_object["��Դ"] = pchar;


			//pchar += strlen(pchar) + 1; //pcharָ��ComputerName[]
			//sprintf(Buffer, "�����\t%s\n", pchar); //������
			//Result += Buffer;
			log_object["�����"] = pchar;

			pchar += strlen(pchar) + 1;	// pcharָ��UserSid
			if(ptr->UserSidLength > 0)
			{
				char Name[64];
				DWORD Length = sizeof(SID), Length1 = sizeof(Buffer);
				SID_NAME_USE Type = SidTypeUser;
				SID *sid = (SID *)(Data + ptr->UserSidOffset);
				if(LookupAccountSid(NULL, sid, Name, &Length, Buffer, &Length1, &Type))
				{
					//�����û���
					//sprintf(Buffer, "�û�\t%s\n", Name); //�û���  
					//Result+=Buffer; 
					log_object["�û�"] = Name;

				}
			}
			if(ptr->DataOffset > ptr->StringOffset) //��ȡ�¼����� 
			{
				//Result += "[����]\t"; 
				pchar = Data + i + ptr->StringOffset; 
				for(short j = 0; j < ptr->NumStrings; j++) 
				{
					//Result += pchar; 
					if(j < ptr->NumStrings-1)
						//Result += ' '; 
					pchar += strlen(pchar) + 1;
				} 
				//Result += '\n'; 
				// Result+="[����]/n"; 
				log_object["[����]"] = pchar;
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