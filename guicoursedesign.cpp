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
    this->setWindowTitle("��¼");
}
void GUICourseDesign::on_AdminButton_clicked()
{
    auto adminlogin = new  AdminLoginWidget;
    adminlogin->setWindowTitle("����Ա��¼");
    adminlogin->show();
    this->hide();
}
void GUICourseDesign::on_CustomerButton_clicked()
{
    auto customerlogin = new  CustomerLoginWidget;
    customerlogin->setWindowTitle("�û����");
    customerlogin->show();
    this->hide();
}
//int _customerno_ = 0;
//string _phone_ = "";