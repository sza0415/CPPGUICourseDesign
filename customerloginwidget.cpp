#include "customerloginwidget.h"
#include"guicoursedesign.h"
#include"customerwidget.h"
#include"adminwidget.h"
#include"global.h"
#include"DbConnection.h"
#include"DbException.h"
#include<string>
#include<iostream>

using namespace std;
#pragma execution_character_set("utf-8")
CustomerLoginWidget::CustomerLoginWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

CustomerLoginWidget::~CustomerLoginWidget()
{
}
void CustomerLoginWidget::setphone(string phone)
{
	phone_ = phone;
}
string CustomerLoginWidget::getphone()
{
	return phone_;
}
void CustomerLoginWidget::setcustomerno(int customerno)
{
	customerno_ = customerno;
}
int CustomerLoginWidget::getcustomerno()
{
	return customerno_;
}
void CustomerLoginWidget::on_back_clicked()
{
	auto guicoursedesign = new GUICourseDesign;
	guicoursedesign->setWindowTitle("�û����");
	guicoursedesign->show();
	delete this;
}
void CustomerLoginWidget::on_login_clicked()
{

	try {
		DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
		//ִ��select�����ȡ�����
		const char* sql;
		QString phoneqstring = ui.phone->text();
		if (phoneqstring == "")
		{
			ui.warn->setText("��ϵ��ʽ����Ϊ��");
			return;
		}		
		string phonestring = phoneqstring.toStdString();
		setphone(phonestring);
		string stringsql1 = "select * from `user` where phone='" + phonestring + "';";
		sql = stringsql1.c_str();
		MYSQL_RES res = db.executeQuery(sql);
		//�����ѯ���Ľ�����е�ÿ����¼�е�����
		MYSQL_ROW row;
		row = mysql_fetch_row(&res);
		if (row == nullptr)
		{
			string stringsql2 = "INSERT INTO `user` (phone) VALUES(" + phonestring + ");";
			db.executeSQL(stringsql2.c_str());
			string stringsql3= "SELECT user_id FROM `user` WHERE phone=" + phonestring + ";";
			MYSQL_RES res = db.executeQuery(stringsql3.c_str());
			MYSQL_ROW row = mysql_fetch_row(&res);
			std::stringstream stream;
			stream << row[0];
			//_customerno_ = stoi(stream.str());
			setcustomerno(stoi(stream.str()));
			auto customerwidget = new CustomerWidget(getcustomerno(), getphone());
			customerwidget->setWindowTitle("�㵥");
			customerwidget->show();
			this->hide();
		}
		else
		{
			string stringsql3 = "SELECT user_id FROM `user` WHERE phone=" + phonestring + ";";
			MYSQL_RES res = db.executeQuery(stringsql3.c_str());
			MYSQL_ROW row = mysql_fetch_row(&res);
			std::stringstream stream;
			stream.clear();
			stream << row[0];
			//_customerno_ = stoi(stream.str());
			setcustomerno(stoi(stream.str()));
			auto customerwidget = new CustomerWidget(getcustomerno(), getphone());
			customerwidget->setWindowTitle("�㵥");
			customerwidget->show();
			this->hide();
		}
	}
	catch (DbExcepiton exp) {
		cout << exp.what() << endl;
	}
}