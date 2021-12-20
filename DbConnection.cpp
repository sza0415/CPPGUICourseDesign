#include"DbConnection.h"
#include"DbException.h"

DbConnection::DbConnection(const char* host, const char* username, const char* password, const char* database)
{
     //��ʼ��MySQL���Ӷ���
     mysql_init(&connection);
     //����MySQL����
     //���ӳɹ�
     if(NULL == mysql_real_connect(&connection, host, username, password, database, 3307, nullptr, 0))
        throw DbExcepiton(mysql_error(&connection));
    //���ò�ѯ����Ϊgbk����֧������
    mysql_query(&connection, "set names utf8mb4");
}
DbConnection::~DbConnection(){
    mysql_close(&connection);
}
MYSQL_RES  DbConnection::executeQuery(const char* sql)
{
    //ִ��SQL����
    int res = mysql_query(&connection, sql);

    if(res) //ִ��ʧ��
        throw DbExcepiton(mysql_error(&connection));
    else
    {
        //��ȡ�����
        MYSQL_RES* res_ptr = mysql_store_result(&connection);
        //�����ȡ�ɹ�
        if(res_ptr)
            return *res_ptr;
        else throw DbExcepiton(mysql_error(&connection));
    }
}
 int DbConnection::executeSQL(const char* sql)
 {
    //ִ��SQL����
    int res = mysql_query(&connection, sql);

    if(res) //ִ��ʧ��
        throw DbExcepiton(mysql_error(&connection));
    else
    {
        return mysql_affected_rows(&connection);
    }
 }
