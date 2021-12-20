#ifndef DBCONNECTION_H_INCLUDED
#define DBCONNECTION_H_INCLUDED
#include "mysql.h"
#pragma once
class DbConnection{
public:
    DbConnection(const char*, const char*, const char*, const char*);
    ~DbConnection();
    MYSQL_RES executeQuery(const char* sql);//查询成功，返回结果集，失败，抛出异常
    int executeSQL(const char* sql);
private:
    MYSQL connection;
};


#endif // DBCONNECTION_H_INCLUDED
