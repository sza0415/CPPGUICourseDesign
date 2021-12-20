#include "guicoursedesign.h"
#include "adminloginwidget.h"
#include"customerloginwidget.h"
#include"global.h"
#include<iostream>
#include<iomanip>
#pragma execution_character_set("utf-8")
GUICourseDesign::GUICourseDesign(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    this->setWindowTitle("登录");
}
void GUICourseDesign::on_AdminButton_clicked()
{
    auto adminlogin = new  AdminLoginWidget;
    adminlogin->setWindowTitle("管理员登录");
    adminlogin->show();
    this->hide();
}
void GUICourseDesign::on_CustomerButton_clicked()
{
    auto customerlogin = new  CustomerLoginWidget;
    customerlogin->setWindowTitle("用户入口");
    customerlogin->show();
    this->hide();
}
//int _customerno_ = 0;
//string _phone_ = "";