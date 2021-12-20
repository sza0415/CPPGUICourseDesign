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
	guicoursedesign->setWindowTitle("�û����");
	guicoursedesign->show();
	delete this;
}
void AdminLoginWidget::on_login_clicked()
{
	try {
		DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
		//ִ��select�����ȡ�����
		const char* sql;
		QString accountqstring= ui.account->text();
		if (accountqstring == "")
		{
			ui.warn->setText("�˺�����Ϊ��");
			return ;
		}
		QString passwordqstring = ui.password->text();
		if (passwordqstring == "")
		{
			ui.warn->setText("��������Ϊ��");
			return;
		}
		std::string accountstring = accountqstring.toStdString();
		std::string stringsql= "select account from `admin` where account='"+accountstring+"';";
		sql = stringsql.c_str();
		MYSQL_RES res = db.executeQuery(sql);
		//�����ѯ���Ľ�����е�ÿ����¼�е�����
		MYSQL_ROW row;
		row = mysql_fetch_row(&res);
		if (row == nullptr)
		{
			ui.warn->setText("�˺Ż��������");
		}
		else if(row[0]== accountstring)
		{
			std::string passwordstring = passwordqstring.toStdString();
			std::string stringsql = "select password from `admin` where account='" + accountstring + "';";
			sql = stringsql.c_str();
			MYSQL_RES res = db.executeQuery(sql);
			//�����ѯ���Ľ�����е�ÿ����¼�е�����
			MYSQL_ROW row;
			row = mysql_fetch_row(&res);
			if (passwordqstring == "")
			{
				ui.warn->setText("��������Ϊ��");
				return;
			}
			if (row == nullptr)ui.warn->setText("�˺Ż��������");
			else if (row[0] == passwordstring)
			{
				auto adminwidget = new AdminWidget;
				adminwidget->setWindowTitle("����˵�");
				adminwidget->show();
				this->hide();
			}
			else ui.warn->setText("�˺Ż��������");
		}
		else ui.warn->setText("�˺Ż��������");
	}
	catch (DbExcepiton exp) {
		std::cout << exp.what() << std::endl;
	}
}

