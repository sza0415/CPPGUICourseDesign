#include "customerwidget.h"
#include"customerloginwidget.h"
#include"managerclass.h"
#include"DbConnection.h"
#include"DbException.h"
#include<map>
#include<iomanip>
#include<iostream>

#pragma execution_character_set("utf-8")
using namespace std;

map<int, OrderDetail*> tempcart;
CustomerWidget::CustomerWidget(int customerno, string phone, QWidget* parent): QWidget(parent)
{
	customerno_ = customerno;
	phone_ = phone;
	ui.setupUi(this);
	try {
		std::stringstream stream;
		string str;
		DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
		//ִ��select�����ȡ�����
		const char* sql;
		sql = "SELECT sku_no,sku_name,price,discount*10,convert(price*discount,decimal(10,2)) FROM `sku`;";
		MYSQL_RES res = db.executeQuery(sql);
		//����ֶ���
		unsigned int num_fields = mysql_num_fields(&res);
		MYSQL_FIELD* fields = mysql_fetch_fields(&res);
		stream << left << setw(30) << "���" << left << setw(30) << "����" << left << setw(30) << "ԭ��" << left << setw(30) << "�ۿ�" << left << setw(30) << "�ּ�" << endl;
		str = stream.str();
		stream.clear();
		ui.menu->setText(str.c_str());
		//�����ѯ���Ľ�����е�ÿ����¼�е�����
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(&res)))
		{
			for (unsigned int i = 0; i < num_fields; i++)
			{
				if (row[i] != 0)stream << left << setw(30) << row[i];
				else stream << left << setw(30) << "NULL";
			}
			stream << setw(30) << endl;
			str = stream.str();
			ui.menu->setText(str.c_str());
			stream.clear();
		}
	}
	catch (DbExcepiton exp) {
		cout << exp.what() << endl;
	}
	//baseorder test;
	stringstream stream;
	stream << left << setw(30) << "���" << left << setw(30) << "����" << left << setw(30) << "ԭ��" << left << setw(30) << "�ۿ�" << left << setw(30) << "�ּ�" << endl;
	ui.menu->setText(stream.str().c_str());
	stream.str("");
	stream << left << setw(30) << "���" << left << setw(30) << "����" <<  left << setw(30) << "�ּ�" << left << setw(30) << "����";
	ui.cart->setText(stream.str().c_str());
	on_refreshmenu_clicked();
}

CustomerWidget::~CustomerWidget()
{
}

void CustomerWidget::on_refreshmenu_clicked()
{
	
	try {
		std::stringstream stream;
		string str;
		DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
		//ִ��select�����ȡ�����
		const char* sql;
		sql = "SELECT sku_no,sku_name,price,discount*10,convert(price*discount,decimal(10,2)) FROM `sku`;";
		MYSQL_RES res = db.executeQuery(sql);
		//����ֶ���
		unsigned int num_fields = mysql_num_fields(&res);
		MYSQL_FIELD* fields = mysql_fetch_fields(&res);
		/*
		for (unsigned int i = 0; i < num_fields; i++) {
			cout.width(20); cout.setf(ios::left);
			stream << left << setw(16) << fields[i].name;
		};
		stream << left << setw(16) << endl;
		*/
		stream << left << setw(30) << "���"  << left << setw(30) << "����"  << left << setw(30) << "ԭ��"  << left << setw(30) << "�ۿ�" << left << setw(30)<<"�ּ�" << endl;
		str = stream.str();
		stream.clear();
		ui.menu->setText(str.c_str());
		//�����ѯ���Ľ�����е�ÿ����¼�е�����
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(&res)))
		{
			for (unsigned int i = 0; i < num_fields; i++)
			{
				if (row[i] != 0)stream << left << setw(30) << row[i];
				else stream << left << setw(30) << "NULL";
			}
			stream << setw(30) << endl;
			str = stream.str();
			ui.menu->setText(str.c_str());
			stream.clear();
		}
	}
	catch (DbExcepiton exp) {
		cout << exp.what() << endl;
	}
}

void CustomerWidget::on_addtocart_clicked()
{
	stringstream stream;
	string str;
	auto orderdetail = new OrderDetail;
	orderdetail->initamount(ui.amount->text().toInt());
	orderdetail->initskuid(ui.skuid->text().toInt());
	auto beforesize = tempcart.size();
	tempcart.insert(make_pair(ui.skuid->text().toInt(), orderdetail));
	auto aftersize = tempcart.size();
	int test = atoi(ui.skuid->text().toStdString().c_str());
	auto test1 = tempcart.end();
	auto test2 = tempcart.find(atoi(ui.skuid->text().toStdString().c_str()));
	//�ж��Ƿ��ǵ�һ�����빺�ﳵ�Ĳ�Ʒ
	if (beforesize==aftersize&&tempcart.end() != (tempcart.find(atoi(ui.skuid->text().toStdString().c_str()))))
	{
		tempcart.at((atoi(ui.skuid->text().toStdString().c_str())))->initamount(tempcart.at((atoi(ui.skuid->text().toStdString().c_str())))->getamount() + ui.amount->text().toInt());
		try {
			DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
			//ִ��select�����ȡ�����
			const char* sql;
			string stringsql = "SELECT sku_no,sku_name,price,discount*10,convert(price*discount,decimal(10,2)) FROM `sku` WHERE sku_no=" + (ui.skuid->text()).toStdString() + "; ";
			sql = stringsql.c_str();
			MYSQL_RES res = db.executeQuery(sql);
			//����ֶ���
			unsigned int num_fields = mysql_num_fields(&res);
			MYSQL_FIELD* fields = mysql_fetch_fields(&res);
			//�����ѯ���Ľ�����е�ÿ����¼�е�����
			MYSQL_ROW row;
			while ((row = mysql_fetch_row(&res)))
			{
				stringstream streamcurrentprice;
				streamcurrentprice << row[4];
				orderdetail->initcurrentprice(atof(streamcurrentprice.str().c_str()));
				for (unsigned int i = 0; i < num_fields; i++)
				{
					if (row[i] != 0 && i != 2 && i != 3)stream << left << setw(30) << row[i];
				}
				stream << left << setw(30) << ui.amount->text().toStdString();
				//stream << setw(30) << endl;
				str = stream.str();
				ui.cart->append(str.c_str());
				stream.clear();
			}
		}
		catch (DbExcepiton exp) {
			cout << exp.what() << endl;
		}
		return;
	}
	else
	{
		try {
			DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
			//ִ��select�����ȡ�����
			const char* sql;
			if (ui.skuid->text() == "")
			{
				ui.skuwarn->setText("����Ϊ��");
				return;
			}
			if (ui.amount->text() == "")
			{
				ui.skuwarn->setText("����Ϊ��");
				return;
			}

			string stringsql = "SELECT sku_no,sku_name,price,discount*10,convert(price*discount,decimal(10,2)) FROM `sku` WHERE sku_no=" + (ui.skuid->text()).toStdString() + "; ";
			sql = stringsql.c_str();
			MYSQL_RES res = db.executeQuery(sql);
			//����ֶ���
			unsigned int num_fields = mysql_num_fields(&res);
			MYSQL_FIELD* fields = mysql_fetch_fields(&res);
			//�����ѯ���Ľ�����е�ÿ����¼�е�����
			MYSQL_ROW row;
			while ((row = mysql_fetch_row(&res)))
			{
				if (row == NULL)
				{
					ui.skuwarn->setText("�޴˲�Ʒ");
					return;
				}
				stringstream streamcurrentprice;
				streamcurrentprice << row[4];
				orderdetail->initcurrentprice(atof(streamcurrentprice.str().c_str()));
				for (unsigned int i = 0; i < num_fields; i++)
				{
					if (row[i] != 0 && i != 2 && i != 3)stream << left << setw(30) << row[i];
				}
				stream << left << setw(30) << ui.amount->text().toStdString();
				//stream << setw(30) << endl;
				str = stream.str();
				ui.cart->append(str.c_str());
				stream.clear();
			}
		}
		catch (DbExcepiton exp) {
			cout << exp.what() << endl;
		}
	}
	
}

void CustomerWidget::on_clearcart_clicked()
{
	tempcart.clear();
	stringstream stream;
	stream.str("");
	stream << left << setw(30) << "���" << left << setw(30) << "����" << left << setw(30) << "�ּ�" << left << setw(30) << "����" << endl;
	ui.cart->setText(stream.str().c_str());
}

void CustomerWidget::on_makedineorder_clicked()
{
	if (ui.diningtableid->text().isEmpty())
	{
		ui.dinewarn->setText("������Ϊ��");
		return;
	}
	else if (ui.diningroomfee->text().isEmpty())
	{
		ui.dinewarn->setText("������Ϊ��");
		return;
	}
	else if (tempcart.size() == 0)
	{
		ui.dinewarn->setText("���ﳵΪ��");
		return;
	}
	else
	{
		ui.dinewarn->setText("");
		map<int, OrderDetail*> cart;
		DineOrder dineorder(customerno_,phone_);
		double totalprice = 0;
		dineorder.initdiningroomfee(stof(ui.diningroomfee->text().toStdString()));
		dineorder.initdiningtableid(stof(ui.diningtableid->text().toStdString()));
		for (auto iter = tempcart.begin(); iter != tempcart.end(); iter++)
		{
			iter->second->initorderid(dineorder.getorderid());
		}
		cart.merge(tempcart);
		for (auto iter = cart.begin(); iter != cart.end(); iter++)
		{
			try 
			{
				DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
				string stringsql1 = "insert into `orderdetail` VALUES("+ to_string(dineorder.getorderid())+","+to_string(iter->second->getskuid())+","
					+ to_string(iter->second->getamount()) + "," + to_string(iter->second->getcurrentprice()) + ");";
				db.executeSQL(stringsql1.c_str());
				totalprice += double(iter->second->getamount()) * iter->second->getcurrentprice();
			}
			catch (DbExcepiton exp) {
				cout << exp.what() << endl;
			}
		}
		try
		{
			DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
			dineorder.inittotalprice(totalprice);
			totalprice += dineorder.getdiningroomfee();
			string stringsql2 = "update `order` set diningtable_id=" + to_string(dineorder.getdiningtableid()) + ", diningroom_fee="
				+ to_string(dineorder.getdiningroomfee()) + ", totalprice=" + to_string(totalprice) + " WHERE order_id=" + to_string(dineorder.getorderid()) + ";";
			db.executeSQL(stringsql2.c_str());
		}
		catch (DbExcepiton exp) {
			cout << exp.what() << endl;
		}
		//��ӡ����
		try {
			std::stringstream stream;
			string str;
			DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
			//ִ��select�����ȡ�����
			QString QStringsql;
			string stringsql;
			const char* sql;
			stringsql = "SELECT order_id,order_time,diningtable_id,diningroom_fee,sku_no,price,amount FROM `order` Natural join `orderdetail` where order_id ='" + to_string(dineorder.getorderid()) + "'";
			sql = stringsql.c_str();
			MYSQL_RES res = db.executeQuery(sql);
			//����ֶ���
			unsigned int num_fields = mysql_num_fields(&res);
			MYSQL_FIELD* fields = mysql_fetch_fields(&res);
			for (unsigned int i = 0; i < num_fields; i++) {
				stream << left << setw(16) << fields[i].name;
			};
			stream << left << setw(16) << endl;
			str = stream.str();
			stream.clear();
			ui.dineorder->setText(str.c_str());
			//�����ѯ���Ľ�����е�ÿ����¼�е�����
			MYSQL_ROW row;
			while ((row = mysql_fetch_row(&res)))
			{
				for (unsigned int i = 0; i < num_fields; i++)
				{
					cout.width(20); cout.setf(ios::left);
					if (row[i] != 0)stream << left << setw(16) << row[i];
					else stream << left << setw(16) << "NULL";
				}
				stream << endl;
				str = stream.str();
				ui.dineorder->setText(str.c_str());
				stream.clear();
			}
			totalprice += dineorder.gettotalprice();
			string stringtotalpriceoutput = "total price:  " + to_string(totalprice).substr(0, to_string(totalprice).find(".") + 3);
			QString qstringtotalpriceoutput;
			ui.dineorder->append(stringtotalpriceoutput.c_str());
		}
		catch (DbExcepiton exp) {
			cout << exp.what() << endl;
		}

	}
	on_clearcart_clicked();
}

void CustomerWidget::on_back_clicked()
{
	auto customerlogin = new  CustomerLoginWidget;
	customerlogin->setWindowTitle("�û����");
	customerlogin->show();
	delete this;
}

void CustomerWidget::on_makedeliverorder_clicked()
{
	if (ui.deliverlocation->text().isEmpty())
	{
		ui.deliverwarn->setText("������Ϊ��");
		return;
	}
	else if (ui.delivertime->text().isEmpty())
	{
		ui.deliverwarn->setText("������Ϊ��");
		return;
	}
	else if (ui.servicefee->text().isEmpty())
	{
		ui.deliverwarn->setText("������Ϊ��");
		return;
	}
	else if (tempcart.size() == 0)
	{
		ui.deliverwarn->setText("���ﳵΪ��");
		return;
	}
	else
	{
		ui.deliverwarn->setText("");
		map<int, OrderDetail*> cart;
		DeliverOrder deliverorder(customerno_,phone_);
		double totalprice = 0;
		string test = ui.phone->text().toStdString();
		deliverorder.initdelivertime(ui.delivertime->text().toStdString());
		deliverorder.initdeliverlocation(ui.deliverlocation->text().toStdString());
		deliverorder.initservicefee(stof(ui.servicefee->text().toStdString()));
		if (!ui.phone->text().isEmpty())
		deliverorder.initphone(ui.phone->text().toStdString());
		for (auto iter = tempcart.begin(); iter != tempcart.end(); iter++)
		{
			iter->second->initorderid(deliverorder.getorderid());
		}
		cart.merge(tempcart);
		for (auto iter = cart.begin(); iter != cart.end(); iter++)
		{
			try
			{
				DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
				string stringsql1 = "insert into `orderdetail` VALUES(" + to_string(deliverorder.getorderid()) + "," + to_string(iter->second->getskuid()) + ","
					+ to_string(iter->second->getamount()) + "," + to_string(iter->second->getcurrentprice()) + ");";
				db.executeSQL(stringsql1.c_str());
				totalprice += double(iter->second->getamount()) * iter->second->getcurrentprice();
			}
			catch (DbExcepiton exp) {
				cout << exp.what() << endl;
			}
		}
		try
		{
			DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
			deliverorder.inittotalprice(totalprice);
			totalprice += deliverorder.getservicefee();
			string stringsql2 = "update `order` set deliver_time=" + deliverorder.getdelivertime() + ", deliver_location='"
				+ deliverorder.getdeliverlocation() + "' , phone=" + deliverorder.getphone() + ", service_fee=" + to_string(deliverorder.getservicefee()) 
				+ ", totalprice=" + to_string(totalprice) + " WHERE order_id=" + to_string(deliverorder.getorderid()) + ";";
			db.executeSQL(stringsql2.c_str());
		}
		catch (DbExcepiton exp) {
			stringstream debug0;
			debug0<< exp.what() << endl;
		}
		//��ӡ����
		try {
			std::stringstream stream;
			string str;
			DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
			//ִ��select�����ȡ�����
			QString QStringsql;
			string stringsql;
			const char* sql;
			stringsql = "SELECT order_id,order_time,deliver_time,deliver_location,phone,service_fee,sku_no,price,amount FROM `order` Natural join `orderdetail` where order_id ='" + to_string(deliverorder.getorderid()) + "'";
			sql = stringsql.c_str();
			MYSQL_RES res = db.executeQuery(sql);
			//����ֶ���
			unsigned int num_fields = mysql_num_fields(&res);
			MYSQL_FIELD* fields = mysql_fetch_fields(&res);
			for (unsigned int i = 0; i < num_fields; i++) {
				cout.width(20); cout.setf(ios::left);
				stream << left << setw(16) << fields[i].name;
			};
			stream << left << setw(16) << endl;
			str = stream.str();
			stream.clear();
			ui.deliverorder->setText(str.c_str());
			//�����ѯ���Ľ�����е�ÿ����¼�е�����
			MYSQL_ROW row;
			while ((row = mysql_fetch_row(&res)))
			{
				for (unsigned int i = 0; i < num_fields; i++)
				{
					cout.width(20); cout.setf(ios::left);
					if (row[i] != 0)stream << left << setw(16) << row[i];
					else stream << left << setw(16) << "NULL";
				}
				stream << endl;
				str = stream.str();
				ui.deliverorder->setText(str.c_str());
				stream.clear();
			}
			totalprice += deliverorder.gettotalprice();
			string stringtotalpriceoutput = "total price:  " + to_string(totalprice).substr(0, to_string(totalprice).find(".") + 3);
			QString qstringtotalpriceoutput;
			ui.deliverorder->append(stringtotalpriceoutput.c_str());
		}
		catch (DbExcepiton exp) {
			cout << exp.what() << endl;
		}

	}
	on_clearcart_clicked();
}
