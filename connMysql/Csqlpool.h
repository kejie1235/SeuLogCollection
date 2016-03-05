
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
	bool IniSqlPool( const char *host , const char *name , const char *pwd , unsigned int port , unsigned int conMax );  //初始化连接池
	bool SelectDB( MYSQL *sql, const char *DB);	//选择数据库
	MYSQL *GetConnect();          // 获取连接
	void RelConnect(MYSQL *sql) ;  // 释放连接
	MYSQL_RES* GetQuery( MYSQL *sql , const char *query);      //mysql操作  增删查改
	void RelQuery(MYSQL_RES *res);   //释放MYSQL_RES资源
	bool Query(MYSQL *sql , const char *query);  //增、删、改操作


protected:
	Csqlpool(void);
private:
	list<MYSQL *> m_sql_free;   //空闲连接     
	static Csqlpool *pSqlPool;      
	CRITICAL_SECTION m_session;    //获取空闲线程
};


