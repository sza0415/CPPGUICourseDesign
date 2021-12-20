#ifndef DBCONNECTION_H_INCLUDED
#define DBCONNECTION_H_INCLUDED
#include "mysql.h"
#pragma once
class DbConnection{
public:
    DbConnection(const char*, const char*, const char*, const char*);
    ~DbConnection();
    MYSQL_RES executeQuery(const char* sql);//��ѯ�ɹ������ؽ������ʧ�ܣ��׳��쳣
    int executeSQL(const char* sql);
private:
    MYSQL connection;
};


#endif // DBCONNECTION_H_INCLUDED
