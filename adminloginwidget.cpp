#include "adminloginwidget.h"
#include"adminwidget.h"
#include"guicoursedesign.h"
#include"DbConnection.h"
#include"DbException.h"
#include<iostream>
#include<iomanip>
#include<string>

#pragma execution_character_set("utf-8")
AdminLoginWidget::AdminLoginWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.password->setEchoMode(QLineEdit::Password);
}

AdminLoginWidget::~AdminLoginWidget()
{

}
void AdminLoginWidget::on_back_clicked()
{
	auto guicoursedesign = new GUICourseDesign;
	guicoursedesign->setWindowTitle("用户入口");
	guicoursedesign->show();
	delete this;
}
void AdminLoginWidget::on_login_clicked()
{
	try {
		DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
		//执行select命令，获取结果集
		const char* sql;
		QString accountqstring= ui.account->text();
		if (accountqstring == "")
		{
			ui.warn->setText("账号输入为空");
			return ;
		}
		QString passwordqstring = ui.password->text();
		if (passwordqstring == "")
		{
			ui.warn->setText("密码输入为空");
			return;
		}
		std::string accountstring = accountqstring.toStdString();
		std::string stringsql= "select account from `admin` where account='"+accountstring+"';";
		sql = stringsql.c_str();
		MYSQL_RES res = db.executeQuery(sql);
		//输出查询出的结果集中的每条记录中的数据
		MYSQL_ROW row;
		row = mysql_fetch_row(&res);
		if (row == nullptr)
		{
			ui.warn->setText("账号或密码错误");
		}
		else if(row[0]== accountstring)
		{
			std::string passwordstring = passwordqstring.toStdString();
			std::string stringsql = "select password from `admin` where account='" + accountstring + "';";
			sql = stringsql.c_str();
			MYSQL_RES res = db.executeQuery(sql);
			//输出查询出的结果集中的每条记录中的数据
			MYSQL_ROW row;
			row = mysql_fetch_row(&res);
			if (passwordqstring == "")
			{
				ui.warn->setText("密码输入为空");
				return;
			}
			if (row == nullptr)ui.warn->setText("账号或密码错误");
			else if (row[0] == passwordstring)
			{
				auto adminwidget = new AdminWidget;
				adminwidget->setWindowTitle("管理菜单");
				adminwidget->show();
				this->hide();
			}
			else ui.warn->setText("账号或密码错误");
		}
		else ui.warn->setText("账号或密码错误");
	}
	catch (DbExcepiton exp) {
		std::cout << exp.what() << std::endl;
	}
}

