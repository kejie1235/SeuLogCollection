#include <string>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <windows.h>

using namespace std;

union alignment {
	size_t sz;
	void *ptr;
	double dbl;
};

int ReadSystemEventLog(const char *Src, string &Result, FILE * pFile) 
{
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
			sprintf(Buffer, "�¼�\t%u\n", (short)(ptr->EventID)); //�¼�ID  
			Result += Buffer;
			sprintf(Buffer, "����\t%s\n", pchar); 
			Result += Buffer; 

			//time_t timep;
			//struct tm *p;
			//time(&timep);
			//p = localtime(&timep);
			//tm *ptm = localtime(&timep);

			tm *ptm = localtime((const time_t *)(&(ptr->TimeWritten)));    //ȡ�õ���ʱ��
			sprintf(Buffer, "ʱ��\t%.4hd-%.2hd-%.2hd %.2hd:%.2hd:%.2hd\n",
				ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday,
				ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
			Result += Buffer;
			pchar = Data + sizeof(EVENTLOGRECORD); //pcharָ��SourceName[]
			sprintf(Buffer, "��Դ\t%s\n", pchar); //�¼���Դ 
			Result += Buffer;
			pchar += strlen(pchar) + 1; //pcharָ��ComputerName[]
			sprintf(Buffer, "�����\t%s\n", pchar); //������
			Result += Buffer;
			pchar += strlen(pchar) + 1;	// pcharָ��UserSid
			if(ptr->UserSidLength > 0)
			{
				char Name[64];
				DWORD Length = sizeof(SID), Length1 = sizeof(Buffer);
				SID_NAME_USE Type = SidTypeUser;
				SID *sid = (SID *)(Data + ptr->UserSidOffset);
				if(LookupAccountSid(NULL, sid, Name, &Length, Buffer, &Length1, &Type))  //�����û���
					sprintf(Buffer, "�û�\t%s\n", Name); //�û���  
				Result+=Buffer; 
			}
			if(ptr->DataOffset > ptr->StringOffset) //��ȡ�¼����� 
			{
				Result += "[����]\t"; 
				pchar = Data + i + ptr->StringOffset; 
				for(short j = 0; j < ptr->NumStrings; j++) 
				{
					Result += pchar; 
					if(j < ptr->NumStrings-1)
						Result += ' '; 
					pchar += strlen(pchar) + 1;
				} 
				Result += '\n'; 
				// Result+="[����]/n"; 
			}
			Result+='\n';
			i+=ptr->Length;
		}
	}
	fwrite(Result.c_str(),Result.length(),1,pFile);
	CloseEventLog(Handle);
	return 0;
}
void main()
{
	cout<<"size union; "<<sizeof(union alignment)<<"\n";
	string result;
	FILE *pFile;
	pFile=fopen("EventLog.txt","w");
	if(pFile==NULL)
		return;
	ReadSystemEventLog("System",result,pFile); //��ȡSystem�¼���־
	fclose(pFile);
}