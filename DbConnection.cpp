#include"DbConnection.h"
#include"DbException.h"

DbConnection::DbConnection(const char* host, const char* username, const char* password, const char* database)
{
     //初始化MySQL连接对象
     mysql_init(&connection);
     //建立MySQL连接
     //连接成功
     if(NULL == mysql_real_connect(&connection, host, username, password, database, 3307, nullptr, 0))
        throw DbExcepiton(mysql_error(&connection));
    //设置查询编码为gbk，以支持中文
    mysql_query(&connection, "set names utf8mb4");
}
DbConnection::~DbConnection(){
    mysql_close(&connection);
}
MYSQL_RES  DbConnection::executeQuery(const char* sql)
{
    //执行SQL命令
    int res = mysql_query(&connection, sql);

    if(res) //执行失败
        throw DbExcepiton(mysql_error(&connection));
    else
    {
        //获取结果集
        MYSQL_RES* res_ptr = mysql_store_result(&connection);
        //如果获取成功
        if(res_ptr)
            return *res_ptr;
        else throw DbExcepiton(mysql_error(&connection));
    }
}
 int DbConnection::executeSQL(const char* sql)
 {
    //执行SQL命令
    int res = mysql_query(&connection, sql);

    if(res) //执行失败
        throw DbExcepiton(mysql_error(&connection));
    else
    {
        return mysql_affected_rows(&connection);
    }
 }
