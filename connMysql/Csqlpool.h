
#pragma once
#include <WinSock2.h>
#include <mysql.h>
#include <list>
#include <iostream>

#pragma comment( lib , "libmysql.lib" )

using namespace std;

class Csqlpool
{
public:
	~Csqlpool(void);
	static Csqlpool *GetInstanceSqlPool();
	bool IniSqlPool( const char *host , const char *name , const char *pwd , unsigned int port , unsigned int conMax );  //��ʼ�����ӳ�
	bool SelectDB( MYSQL *sql, const char *DB);	//ѡ�����ݿ�
	MYSQL *GetConnect();          // ��ȡ����
	void RelConnect(MYSQL *sql) ;  // �ͷ�����
	MYSQL_RES* GetQuery( MYSQL *sql , const char *query);      //mysql����  ��ɾ���
	void RelQuery(MYSQL_RES *res);   //�ͷ�MYSQL_RES��Դ
	bool Query(MYSQL *sql , const char *query);  //����ɾ���Ĳ���


protected:
	Csqlpool(void);
private:
	list<MYSQL *> m_sql_free;   //��������     
	static Csqlpool *pSqlPool;      
	CRITICAL_SECTION m_session;    //��ȡ�����߳�
};


