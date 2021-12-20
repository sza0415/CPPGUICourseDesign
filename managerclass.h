#include<iomanip>
#include"global.h"
#include<map>
#include<string>
#include<array>
#include<ctime>
#include<QTextBrowser>
#include<qlabel.h>
class OrderDetail
{
protected:
	int orderid_=-1;
	int skuid_;
	int amount_;
	double currentprice_;
public:
	void initorderid(int orderid);
	void initskuid(int skuid);
	void initamount(int amount);
	int getamount();
	int getskuid();
	double getcurrentprice();
	void initcurrentprice(double currentprice);
};
class BaseOrder
{
protected:
	int orderid_ = -1;
	time_t ordertime_;
	tm* structordertime_;
	int userid_;
	std::string phone_;
	std::string uploadordertime_;
	double totalprice_ = 1.88;
	std::map<int, OrderDetail*>cart;
public:
	BaseOrder(int customerno,std::string phone);
	int getorderid();
	double gettotalprice();
	void inittotalprice(double total);
};
class DineOrder :public BaseOrder
{
protected:
	int diningtableid_=-1;
	double diningroomfee_=-1;
public:
	DineOrder(int customerno, std::string phone);
	void initdiningtableid(int diningtableid);
	void initdiningroomfee(int diningroomfee);
	int getdiningtableid();
	int getdiningroomfee();
};
class DeliverOrder :public BaseOrder
{
protected:
	std::string delivertime_;
	std::string deliverlocation_;
	double servicefee_=-1;
public:
	DeliverOrder(int customerno, std::string phone);
	void initdelivertime(std::string delivertime);
	void initdeliverlocation(std::string deliverlocation);
	void initphone(std::string phone);
	void initservicefee(double servicefee);
	std::string getdelivertime();
	std::string getdeliverlocation();
	std::string getphone();
	double getservicefee();
};
class OrderManager
{
private:
	std::map<int, std::array<std::string, 14>> ordermap_;
public:
	void getdateorder(std::string);
	void orderprint(QTextBrowser*);
	void orderfindbyno(std::string,QTextBrowser*);
	void orderfindbyphone(std::string,QTextBrowser*);
	void delorder(std::string);
	void makeconclusion(std::string,QTextBrowser*);
};
class SkuManager
{
private:
	std::map<int, std::array<std::string, 5>> skumap_;
public:
	void addsku(std::string name, std::string price, std::string discount, QLabel* warn);
	void skufindbyno(std::string, QTextBrowser*);
	void skufindbyname(std::string strname, QTextBrowser* qtextbrowser);
	void altersku(std::string skuno, std::string name, std::string price, std::string discount, QLabel* warn);
	void delsku(std::string delskunostring);
	void resetskubrowser(QTextBrowser*);
};
class OrderList
{
private:
	std::map<int, DineOrder*> dineorderlist_;
	std::map<int, DeliverOrder*> deliverorderlist_;
public:
	void insertdineorder(DineOrder* dineorder);
	void printdineorder(DineOrder* dineorder, QTextBrowser* dineorderbrowser);
	void uploaddineorder(DineOrder* dineorder);
	void insertdeliverorder(DeliverOrder* deliverorder);
	void printdeliverorder(DeliverOrder* deliverorder, QTextBrowser* deliverorderbrowser);
	void uploaddeliverorder(DeliverOrder* deliverorder);
	//testpurpose
	//testpurpose2
};