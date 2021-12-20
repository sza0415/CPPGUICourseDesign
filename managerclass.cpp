#include "managerclass.h"
#include"mysql.h"
#include"DbConnection.h"
#include"DbException.h"
#include<iostream>
#pragma execution_character_set("utf-8")
using namespace std;
inline string addprefix0(int& x)
{
	stringstream streamprefix0;
	if (x <= 9)streamprefix0 << "0" << x;
	else streamprefix0 << x;
	string stringprefixed = streamprefix0.str();
	return stringprefixed;
}
BaseOrder::BaseOrder(int customerno, string phone)
{
	userid_ = customerno;
	phone_ = phone;
	ordertime_ = time(0);
	structordertime_ = localtime(&ordertime_);
	string month = addprefix0(++structordertime_->tm_mon);
	string day = addprefix0(structordertime_->tm_mday);
	string minute = addprefix0(structordertime_->tm_min);
	string hour = addprefix0(structordertime_->tm_hour);
	uploadordertime_ = std::to_string(structordertime_->tm_year + 1900) + month
		+ day + hour + minute;

	//获取orderid赋给orderid_
	try {
		DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
		//执行select命令，获取结果集
		string stringsql0;
		string stringuserid = to_string(userid_);
		string stringprice = to_string(totalprice_);
		stringsql0 = "insert into `order` (user_id,order_time,phone,totalprice) VALUES("+stringuserid+",'"+uploadordertime_+"'," + phone_ + "," +stringprice+");";
		const char* sql0 = stringsql0.c_str();
		db.executeSQL(sql0);
		const char* sql;
		string stringsql1 = "select max(order_id) from `order`;";
		sql = stringsql1.c_str();
		MYSQL_RES res = db.executeQuery(sql);
		//输出查询出的结果集中的每条记录中的数据
		MYSQL_ROW row;
		row = mysql_fetch_row(&res);
		if (row != nullptr)
		{
			std::stringstream stream;
			stream << row[0];
			orderid_ = stoi(stream.str());
		}
		else
		{
			return;
		}
	}
	catch (DbExcepiton exp) {
		cout << exp.what() << endl;
	}
}
DeliverOrder::DeliverOrder(int customerno, string phone) :BaseOrder(customerno, phone){}
DineOrder::DineOrder(int customerno, string phone) : BaseOrder(customerno, phone){}
int BaseOrder::getorderid()
{
	return orderid_;
}

void DineOrder::initdiningtableid(int diningtableid)
{
	diningtableid_ = diningtableid;
}

void DineOrder::initdiningroomfee(int diningroomfee)
{
	diningroomfee_ = diningroomfee;
}

int DineOrder::getdiningtableid()
{
	return diningtableid_;
}

int DineOrder::getdiningroomfee()
{
	return diningroomfee_;
}

double BaseOrder::gettotalprice()
{
	return totalprice_;
}
void BaseOrder::inittotalprice(double totalprice)
{
	totalprice_ = totalprice;
}

void DeliverOrder::initdelivertime(string delivertime)
{
	delivertime_ = delivertime;
}

void DeliverOrder::initdeliverlocation(string deliverlocation)
{
	deliverlocation_ = deliverlocation;
}

void DeliverOrder::initphone(string phone)
{
	phone_ = phone;
}

void DeliverOrder::initservicefee(double servicefee)
{
	servicefee_ = servicefee;
}

string DeliverOrder::getdelivertime()
{
	return delivertime_;
}

string DeliverOrder::getdeliverlocation()
{
	return deliverlocation_;
}

string DeliverOrder::getphone()
{
	return phone_;
}

double DeliverOrder::getservicefee()
{
	return servicefee_;
}

void OrderDetail::initorderid(int orderid)
{
	orderid_ = orderid;
}

void OrderDetail::initskuid(int skuid)
{
	skuid_ = skuid;
}

void OrderDetail::initamount(int amount)
{
	amount_ = amount;
}

int OrderDetail::getamount()
{
	return amount_;
}

int OrderDetail::getskuid()
{
	return skuid_;
}

double OrderDetail::getcurrentprice()
{
	return currentprice_;
}

void OrderDetail::initcurrentprice(double currentprice)
{
	currentprice_ = currentprice;
}

void OrderManager::getdateorder(string date)
{
	try 
	{
		std::stringstream stream;
		string str;
		DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
		//执行select命令，获取结果集
		string stringsql;
		const char* sql;
		stringsql = "SELECT * FROM `order` Natural join `orderdetail` where order_time LIKE '" + date + "%'";
		sql = stringsql.c_str();
		MYSQL_RES res = db.executeQuery(sql);
		//输出查询出的结果集中的每条记录中的数据，写入数组，数组insert进一个map
		MYSQL_ROW row;
		array<string, 14> sqldata;
		int iter = 0;
		while ((row = mysql_fetch_row(&res)))
		{
			for (unsigned int i = 0; i < 14; i++)
			{
				if (row[i] != 0)
				{
					stream << row[i];
					sqldata[i] = stream.str();
					stream.str("");
				}
				else
				{
					stream << "NULL";
					sqldata[i] = stream.str();
					stream.str("");
				}
			}
			ordermap_.insert(make_pair(iter, sqldata));
			iter++;
		}
	}
	catch (DbExcepiton exp) {
		cout << exp.what() << endl;
	}
}

void OrderManager::orderprint(QTextBrowser* qtextbrowser)
{
	
	stringstream stream;
	stream << left << setw(16) << "订单号" << left << setw(16) << "用户ID" << left << setw(16) << "餐厅ID" << left << setw(16) << "       下单时间" 
		<< left << setw(16) << "        餐桌ID"<< left << setw(16) << "        包厢费" << left << setw(16) << "        外卖预约时间" << left << setw(16) << "        地址" 
		<< left << setw(16) << "        手机号码" << left << setw(16) << "        外送费"<< left << setw(16) << "           总价" << left << setw(16) << "           菜品编号" 
		<< left << setw(16) << "           数量" << left << setw(16) << "           单价";
	qtextbrowser->setText(stream.str().c_str());
	stream.str("");
	for (auto iter = ordermap_.begin(); iter != ordermap_.end(); iter++)
	{
		for (int i=0;i<14;i++)
		{
			stream << left << setw(16) << iter->second[i];
		}
		qtextbrowser->append(stream.str().c_str());
		stream.str("");
	}
	ordermap_.clear();
}

void OrderManager::orderfindbyno(std::string strno, QTextBrowser* qtextbrowser)
{
	try
	{
		std::stringstream stream;
		string str;
		DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
		//执行select命令，获取结果集
		string stringsql;
		const char* sql;
		stringsql = "SELECT * FROM `order` Natural join `orderdetail` where order_id = '" + strno + "';";
		sql = stringsql.c_str();
		MYSQL_RES res = db.executeQuery(sql);
		//输出查询出的结果集中的每条记录中的数据，写入数组，数组insert进一个map
		MYSQL_ROW row;
		array<string, 14> sqldata;
		int iter = 0;
		while ((row = mysql_fetch_row(&res)))
		{
			for (unsigned int i = 0; i < 14; i++)
			{
				if (row[i] != 0)
				{
					stream << row[i];
					sqldata[i] = stream.str();
					stream.str("");
				}
				else
				{
					stream << "NULL";
					sqldata[i] = stream.str();
					stream.str("");
				}
			}
			ordermap_.insert(make_pair(iter, sqldata));
			iter++;
		}
	}
	catch (DbExcepiton exp) {
		cout << exp.what() << endl;
	}
	stringstream stream;
	stream << left << setw(16) << "订单号" << left << setw(16) << "用户ID" << left << setw(16) << "餐厅ID" << left << setw(16) << "       下单时间"
		<< left << setw(16) << "        餐桌ID" << left << setw(16) << "        包厢费" << left << setw(16) << "        外卖预约时间" << left << setw(16) << "        地址"
		<< left << setw(16) << "        手机号码" << left << setw(16) << "        外送费" << left << setw(16) << "           总价" << left << setw(16) << "           菜品编号"
		<< left << setw(16) << "           数量" << left << setw(16) << "           单价";
	qtextbrowser->setText(stream.str().c_str());
	stream.str("");
	for (auto iter = ordermap_.begin(); iter != ordermap_.end(); iter++)
	{
		for (int i = 0; i < 14; i++)
		{
			stream << left << setw(16) << iter->second[i];
		}
		qtextbrowser->append(stream.str().c_str());
		stream.str("");
	}
	ordermap_.clear();
}
void OrderManager::orderfindbyphone(std::string strphone, QTextBrowser* qtextbrowser)
{
	try
	{
		std::stringstream stream;
		string str;
		DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
		//执行select命令，获取结果集
		string stringsql;
		const char* sql;
		stringsql = "SELECT * FROM `order` Natural join `orderdetail` where phone = '" + strphone + "';";
		sql = stringsql.c_str();
		MYSQL_RES res = db.executeQuery(sql);
		//输出查询出的结果集中的每条记录中的数据，写入数组，数组insert进一个map
		MYSQL_ROW row;
		array<string, 14> sqldata;
		int iter = 0;
		while ((row = mysql_fetch_row(&res)))
		{
			for (unsigned int i = 0; i < 14; i++)
			{
				if (row[i] != 0)
				{
					stream << row[i];
					sqldata[i] = stream.str();
					stream.str("");
				}
				else
				{
					stream << "NULL";
					sqldata[i] = stream.str();
					stream.str("");
				}
			}
			ordermap_.insert(make_pair(iter, sqldata));
			iter++;
		}
	}
	catch (DbExcepiton exp) {
		cout << exp.what() << endl;
	}
	stringstream stream;
	stream << left << setw(16) << "订单号" << left << setw(16) << "用户ID" << left << setw(16) << "餐厅ID" << left << setw(16) << "       下单时间"
		<< left << setw(16) << "        餐桌ID" << left << setw(16) << "        包厢费" << left << setw(16) << "        外卖预约时间" << left << setw(16) << "        地址"
		<< left << setw(16) << "        手机号码" << left << setw(16) << "        外送费" << left << setw(16) << "           总价" << left << setw(16) << "           菜品编号"
		<< left << setw(16) << "           数量" << left << setw(16) << "           单价";
	qtextbrowser->setText(stream.str().c_str());
	stream.str("");
	for (auto iter = ordermap_.begin(); iter != ordermap_.end(); iter++)
	{
		for (int i = 0; i < 14; i++)
		{
			stream << left << setw(16) << iter->second[i];
		}
		qtextbrowser->append(stream.str().c_str());
		stream.str("");
	}
	ordermap_.clear();
}
void OrderManager::delorder(std::string delnostring)
{
	try
	{
		std::stringstream stream;
		string str;
		DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
		//执行select命令，获取结果集
		string stringsql = "DELETE FROM	`order` WHERE order_id = " + delnostring + ";";
		const char* sql;
		sql = stringsql.c_str();
		db.executeSQL(sql);
		stringsql = "DELETE FROM orderdetail WHERE order_id = " + delnostring + ";";
		const char* sql1;
		sql1 = stringsql.c_str();
		db.executeSQL(sql1);
	}
	catch (DbExcepiton exp)
	{
		cout << exp.what() << std::endl;
	}
}
void OrderManager::makeconclusion(std::string date,QTextBrowser* qtextbrowser)
{
	try {
		std::stringstream stream;
		string str;
		DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
		//执行select命令，获取结果集
		QString QStringsql;
		string stringsql;
		const char* sql;
		stringsql = "SELECT * FROM `order` where order_time LIKE '" + date + "%'";
		sql = stringsql.c_str();
		MYSQL_RES res = db.executeQuery(sql);
		//输出查询出的结果集中的每条记录中的数据，写入数组，数组insert进一个map
		MYSQL_ROW row;
		map<int, array<string, 11>> sqlmap;
		array<string, 11> sqldata;
		int iter = 0;
		while ((row = mysql_fetch_row(&res)))
		{
			for (unsigned int i = 0; i < 11; i++)
			{
				if (row[i] != 0)
				{
					stream << row[i];
					sqldata[i] = stream.str();
					stream.str("");
				}
				else
				{
					stream << "NULL";
					sqldata[i] = stream.str();
					stream.str("");
				}
			}
			sqlmap.insert(make_pair(iter, sqldata));
			iter++;
		}
		//统计
		int ordercount = 0; double orderprice = 0; int dinecount = 0; int delivercount = 0;
		for (auto iter = sqlmap.begin(); iter != sqlmap.end(); iter++)
		{
			ordercount++;
			if (iter->second[4] != "NULL")dinecount++;
			else delivercount++;
			orderprice += stof(iter->second[10]);
		}
		//处理菜品统计
		stringsql = "SELECT sku_no,amount FROM `order` Natural join `orderdetail` where order_time LIKE '" + date + "%'";
		const char* sql1;
		sql1 = stringsql.c_str();
		res = db.executeQuery(sql1);
		//输出查询出的naturaljoin结果集中的每条记录中的数据，写入map进行统计
		map<int, int> skucount;
		iter = 0;
		while ((row = mysql_fetch_row(&res)))
		{
			auto beforeinsert = skucount.size();
			skucount.insert(make_pair(stoi(row[0]), stoi(row[1])));
			auto afterinsert = skucount.size();
			if (beforeinsert == afterinsert)
			{
				skucount.at(stoi(row[0])) += stoi(row[1]);
			}
		}
		stringstream streamconclusion;
		streamconclusion << "订单总数：" << ordercount << "  销售额：" << orderprice << "  外卖单数占比："
			<< double(delivercount) * 100 / double(delivercount + dinecount) << "%  在店单数占比：" <<
			double(dinecount) * 100 / double(delivercount + dinecount) << "%";
		qtextbrowser->setText(streamconclusion.str().c_str());
		streamconclusion.str("");
		streamconclusion << setw(8) << "菜品SKU";
		qtextbrowser->append(streamconclusion.str().c_str());
		streamconclusion.str("");
		for (auto iter = skucount.begin(); iter != skucount.end(); iter++)
		{
			streamconclusion << setw(8) << iter->first;
		}
		qtextbrowser->append(streamconclusion.str().c_str());
		streamconclusion.str("");
		streamconclusion << setw(8) << "数量";
		qtextbrowser->append(streamconclusion.str().c_str());
		streamconclusion.str("");
		for (auto iter = skucount.begin(); iter != skucount.end(); iter++)
		{
			streamconclusion << setw(8) << iter->second;
		}
		qtextbrowser->append(streamconclusion.str().c_str());
	}
	catch (DbExcepiton exp) {
		cout << exp.what() << std::endl;
	}

}
void SkuManager::delsku(std::string delnostring)
{
	try
	{
		std::stringstream stream;
		string str;
		DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
		//执行select命令，获取结果集
		string stringsql = "DELETE FROM sku WHERE sku_no = '" + delnostring + "';";
		const char* sql;
		sql = stringsql.c_str();
		db.executeSQL(sql);
	}
	catch (DbExcepiton exp)
	{
		cout << exp.what() << std::endl;
	}
}

void SkuManager::addsku(std::string name, std::string price, std::string discount,QLabel* warn)
{
	try
	{
		std::stringstream stream;
		string str;
		DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
		//执行select命令，获取结果集
		if (discount=="")discount = "10";
		if (name=="")
		{
			warn->setText("菜名不能为空");
			return;
		}
		if (price == "")
		{
			warn->setText("价格不能为空");
			return;
		}
		warn->setText("");
		QString qdiscount = discount.c_str();
		discount = to_string((double(qdiscount.toFloat()) / 10)).c_str();
		string stringsql = "INSERT INTO SKU (sku_name,price,discount) VALUES('" + name + "','" + price + "','" + discount + "'); ";
		const char* sql;
		sql = stringsql.c_str();
		db.executeSQL(sql);
	}
	catch (DbExcepiton exp)
	{
		cout << exp.what() << std::endl;
	}

}
void SkuManager::skufindbyno(std::string strno, QTextBrowser* qtextbrowser)
{
	try
	{
		std::stringstream stream;
		string str;
		DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
		//执行select命令，获取结果集
		string stringsql;
		const char* sql;
		stringsql = "SELECT sku_no,sku_name, price, discount * 10, convert(price * discount, decimal(10, 2)) FROM `sku` where sku_no='" + strno + "';";
		sql = stringsql.c_str();
		MYSQL_RES res = db.executeQuery(sql);
		//输出查询出的结果集中的每条记录中的数据，写入数组，数组insert进一个map
		MYSQL_ROW row;
		array<string, 5> sqldata;
		int iter = 0;
		while ((row = mysql_fetch_row(&res)))
		{
			for (unsigned int i = 0; i < 5; i++)
			{
				if (row[i] != 0)
				{
					stream << row[i];
					sqldata[i] = stream.str();
					stream.str("");
				}
				else
				{
					stream << "NULL";
					sqldata[i] = stream.str();
					stream.str("");
				}
			}
			skumap_.insert(make_pair(iter, sqldata));
			iter++;
		}
	}
	catch (DbExcepiton exp) {
		cout << exp.what() << endl;
	}
	stringstream stream;
	stream << left << setw(30) << "编号" << left << setw(30) << "菜名" << left << setw(30) << "原价" << left << setw(30) << "折扣" << left << setw(30) << "现价";
	qtextbrowser->setText(stream.str().c_str());
	stream.str("");
	for (auto iter = skumap_.begin(); iter != skumap_.end(); iter++)
	{
		for (int i = 0; i < 5; i++)
		{
			stream << left << setw(30) << iter->second[i];
		}
		qtextbrowser->append(stream.str().c_str());
		stream.str("");
	}
	skumap_.clear();
}
void SkuManager::skufindbyname(std::string strname, QTextBrowser* qtextbrowser)
{
	try
	{
		std::stringstream stream;
		string str;
		DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
		//执行select命令，获取结果集
		string stringsql;
		const char* sql;
		stringsql = "SELECT sku_no,sku_name, price, discount * 10, convert(price * discount, decimal(10, 2)) FROM `sku` where sku_name='" + strname + "';";
		sql = stringsql.c_str();
		MYSQL_RES res = db.executeQuery(sql);
		//输出查询出的结果集中的每条记录中的数据，写入数组，数组insert进一个map
		MYSQL_ROW row;
		array<string, 5> sqldata;
		int iter = 0;
		while ((row = mysql_fetch_row(&res)))
		{
			for (unsigned int i = 0; i < 5; i++)
			{
				if (row[i] != 0)
				{
					stream << row[i];
					sqldata[i] = stream.str();
					stream.str("");
				}
				else
				{
					stream << "NULL";
					sqldata[i] = stream.str();
					stream.str("");
				}
			}
			skumap_.insert(make_pair(iter, sqldata));
			iter++;
		}
	}
	catch (DbExcepiton exp) {
		cout << exp.what() << endl;
	}
	stringstream stream;
	stream << left << setw(30) << "编号" << left << setw(30) << "菜名" << left << setw(30) << "原价" << left << setw(30) << "折扣" << left << setw(30) << "现价";
	qtextbrowser->setText(stream.str().c_str());
	stream.str("");
	for (auto iter = skumap_.begin(); iter != skumap_.end(); iter++)
	{
		for (int i = 0; i < 5; i++)
		{
			stream << left << setw(30) << iter->second[i];
		}
		qtextbrowser->append(stream.str().c_str());
		stream.str("");
	}
	skumap_.clear();
}
void SkuManager::altersku(std::string skuno,std::string name, std::string price, std::string discount, QLabel* warn)
{
	try
	{
		std::stringstream stream;
		string str;
		DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
		//执行select命令，获取结果集
		if (discount == "")discount = "10";
		if (name == "")
		{
			warn->setText("菜名不能为空");
			return;
		}
		if (price == "")
		{
			warn->setText("价格不能为空");
			return;
		}		
		if (skuno == "")
		{
			warn->setText("价格不能为空");
			return;
		}
		warn->setText("");
		QString qdiscount = discount.c_str();
		discount = to_string((double(qdiscount.toFloat()) / 10)).c_str();
		string stringsql = "UPDATE SKU SET sku_name='" + name + "',price='" + price + "',discount='" + discount + "' WHERE sku_no='" + skuno + "'; ";
		const char* sql;
		sql = stringsql.c_str();
		db.executeSQL(sql);
	}
	catch (DbExcepiton exp)
	{
		cout << exp.what() << std::endl;
	}

}
void SkuManager::resetskubrowser(QTextBrowser* qtextbrowser)
{
	try
	{
		std::stringstream stream;
		string str;
		DbConnection db(databaseinfo.gethost(), databaseinfo.getusername(), databaseinfo.getpassword(), databaseinfo.getdatabase());
		//执行select命令，获取结果集
		string stringsql;
		const char* sql;
		stringsql = "SELECT sku_no,sku_name, price, discount * 10, convert(price * discount, decimal(10, 2)) FROM `sku`;";
		sql = stringsql.c_str();
		MYSQL_RES res = db.executeQuery(sql);
		//输出查询出的结果集中的每条记录中的数据，写入数组，数组insert进一个map
		MYSQL_ROW row;
		array<string, 5> sqldata;
		int iter = 0;
		while ((row = mysql_fetch_row(&res)))
		{
			for (unsigned int i = 0; i < 5; i++)
			{
				if (row[i] != 0)
				{
					stream << row[i];
					sqldata[i] = stream.str();
					stream.str("");
				}
				else
				{
					stream << "NULL";
					sqldata[i] = stream.str();
					stream.str("");
				}
			}
			skumap_.insert(make_pair(iter, sqldata));
			iter++;
		}
	}
	catch (DbExcepiton exp) {
		cout << exp.what() << endl;
	}
	stringstream stream;
	stream << left << setw(30) << "编号" << left << setw(30) << "菜名" << left << setw(30) << "原价" << left << setw(30) << "折扣" << left << setw(30) << "现价";
	qtextbrowser->setText(stream.str().c_str());
	stream.str("");
	for (auto iter = skumap_.begin(); iter != skumap_.end(); iter++)
	{
		for (int i = 0; i < 5; i++)
		{
			stream << left << setw(30) << iter->second[i];
		}
		qtextbrowser->append(stream.str().c_str());
		stream.str("");
	}
	skumap_.clear();
}
//branch1
