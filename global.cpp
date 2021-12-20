#include<global.h>
DatabaseInfo::DatabaseInfo()
{
	host_= "192.168.23.131";
	username_ = "root";
	password_ = "m65821534";
	database_ = "restaurant1";
}

const char* DatabaseInfo::gethost()
{
	return host_.c_str();
}

const char* DatabaseInfo::getusername()
{
	return username_.c_str();
}

const char* DatabaseInfo::getpassword()
{
	return password_.c_str();
}

const char* DatabaseInfo::getdatabase()
{
	return database_.c_str();
}
extern DatabaseInfo databaseinfo;