#include "Csqlpool.h"
//#include "member_pool.h"
#pragma comment( lib , "libmysql.lib" )

int main(){

	Csqlpool *psql = Csqlpool::GetInstanceSqlPool();  

	 if(!psql->IniSqlPool("10.6.12.131" , "root" ,"cpp123456",3306,10))  
    {  
        cout<<"连接错误"<<endl;  
    }  

	 system("pause");
}
















//#include <windows.h>
//#include "stdio.h"
//#include "winsock.h" 
//#include <mysql.h>
//
////mysql 是64位，记住编译平台也要选择X64。
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
//	if ( con !=NULL && mysql_real_connect(con,dbip,dbuser,dbpasswd,dbname,3306/*TCP IP端口*/,NULL/*Unix Socket 连接类型*/,0/*运行成ODBC数据库标志*/) ) 
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
//		printf("连接失败：%s\n", mysql_error(con));
//	}	
//	return 1;
//}