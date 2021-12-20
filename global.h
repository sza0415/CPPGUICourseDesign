#pragma once
#include<fstream>
#include<string>
class DatabaseInfo
{
private:
	std::string host_;
	std::string username_;
	std::string password_;
	std::string database_;
public:
	DatabaseInfo();
	const char* gethost();
	const char* getusername();
	const char* getpassword();
	const char* getdatabase();
};
static DatabaseInfo databaseinfo;