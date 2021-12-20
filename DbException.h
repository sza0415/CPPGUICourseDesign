#include<exception>
#pragma once

class DbExcepiton: public std::exception
{
public:
    DbExcepiton(const char* msg):err_msg(msg){}
    const char* what() const throw(){return err_msg;}
private:
    const char* err_msg;
};
