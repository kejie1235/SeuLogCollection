#include "Csqlpool.h"
//#include "member_pool.h"
#pragma comment( lib , "libmysql.lib" )

int main(){

	Csqlpool *psql = Csqlpool::GetInstanceSqlPool();  

	 if(!psql->IniSqlPool("10.6.12.131" , "root" ,"cpp123456",3306,10))  
    {  
        cout<<"���Ӵ���"<<endl;  
    }  

	 system("pause");
}
















//#include <windows.h>
//#include "stdio.h"
//#include "winsock.h" 
//#include <mysql.h>
//
////mysql ��64λ����ס����ƽ̨ҲҪѡ��X64��
//
//int main()
//{
//
//	MYSQL * con; //= mysql_init((MYSQL*) 0); 
//	MYSQL_RES *res;
//	MYSQL_ROW row;
//
//
//	char tmp[400];
//
//	//database configuartion
//	char dbuser[30]="test"; 
//	char dbpasswd[30]="cpp123456";
//	char dbip[30]="127.0.0.1";
//	char dbname[50]="logdb";
//	//char tablename[50]="test";
//	//char *query=NULL;
//
//
//	int x;
//	int y;
//	int rt;//return value
//	unsigned int t;
//
//	int count = 0;
//
//
//	/*printf("input x,y\n");
//	scanf("%d,%d",&x,&y);
//	fflush(stdin);*/
//	printf("input over\n");
//	con = mysql_init((MYSQL*) 0); 
//
//
//	if ( con !=NULL && mysql_real_connect(con,dbip,dbuser,dbpasswd,dbname,3306/*TCP IP�˿�*/,NULL/*Unix Socket ��������*/,0/*���г�ODBC���ݿ��־*/) ) 
//	{ 
//		if (!mysql_select_db(con,dbname)) 
//		{ 
//			printf("Select successfully the database!\n");             
//			con ->reconnect = 1;    
//		}
//
//	}
//
//	else
//	{
//		printf("����ʧ�ܣ�%s\n", mysql_error(con));
//	}	
//	return 1;
//}