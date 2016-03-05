#include "Csqlpool.h"

Csqlpool *Csqlpool::pSqlPool = NULL;


Csqlpool::Csqlpool(void)
{
	InitializeCriticalSection( &m_session );
}


Csqlpool::~Csqlpool(void)
{
	while ( m_sql_free.size() )
	{
		mysql_close( m_sql_free.front() );
		m_sql_free.pop_front();
	}
	DeleteCriticalSection(&m_session);
}


Csqlpool* Csqlpool::GetInstanceSqlPool()
{
	if (  pSqlPool == NULL )
	{
		return new Csqlpool;
	}
	return pSqlPool;
}

bool Csqlpool::IniSqlPool( const char *host ,const char *name , const char *pwd , unsigned int port , unsigned int conMax )  //��ʼ�����ӳ�
{
	int nsum = 0 ;
	for (unsigned int i = 0 ; i < conMax ;++i  )
	{
		MYSQL *pmysql;
		pmysql = mysql_init( (MYSQL*)NULL );
		if ( pmysql != NULL )
		{
			if ( mysql_real_connect( pmysql , host , name , pwd , NULL , 3306 , NULL , 0 ) )
			{
				m_sql_free.push_back(pmysql);
			}
			else
			{
				printf("����ʧ�ܣ�%s\n", mysql_error(pmysql));
				if ( nsum++ == 100 )
				{
					return false;
				}
				continue;
			}
		}
		continue;
	}
	return true;
}

bool Csqlpool::SelectDB( MYSQL *sql, const char *DB)	//ѡ�����ݿ�
{
	if(mysql_select_db(sql , DB))
	{
		return false;
	}
	return true;
}

MYSQL* Csqlpool::GetConnect()          // ��ȡ����
{
	if ( m_sql_free.size()  )
	{
		EnterCriticalSection(&m_session);
		MYSQL *mysql = m_sql_free.front();
		m_sql_free.pop_front();
		LeaveCriticalSection(&m_session);
		return mysql;
	}
	else
		return NULL;
}

void Csqlpool::RelConnect(MYSQL *sql)  // �ͷ�����
{
	EnterCriticalSection(&m_session);
	m_sql_free.push_back(sql);
	LeaveCriticalSection(&m_session);
}


MYSQL_RES* Csqlpool::GetQuery( MYSQL *sql , const char *query)         //��ѯ����
{
	if ( mysql_query( sql , query ) == 0 )
	{
		return mysql_store_result( sql );
	}
	else
		return NULL;
}

void Csqlpool::RelQuery(MYSQL_RES *res)   //mysql_res release
{
	mysql_free_result(res);
}

bool Csqlpool::Query(MYSQL *sql , const char *query)  //����ɾ���Ĳ���
{
	if ( mysql_query( sql , query ) )
	{
		return false;
	}
	return true;
}