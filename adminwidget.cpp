#include "adminwidget.h"
#include"adminloginwidget.h"
#include"global.h"
#include"DbConnection.h"
#include"DbException.h"
#include<iomanip>
#include<array>
#include<map>
#include<iostream>

#pragma execution_character_set("utf-8")
using namespace std;
AdminWidget::AdminWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	on_reset_clicked();
}

AdminWidget::~AdminWidget()
{
	delete ordermanager_;
	delete skumanager_;
}
void AdminWidget::on_getdateorder_clicked()
{
	string datestring = ui.date->text().toStdString();
	ordermanager_->getdateorder(datestring);
	ordermanager_->orderprint(ui.orderBrowser);
}
void AdminWidget::on_orderfindbyno_clicked()
{
	ordermanager_->orderfindbyno(ui.orderno->text().toStdString(), ui.orderBrowser);
}
void AdminWidget::on_orderfindbyphone_clicked() 
{
	ordermanager_->orderfindbyphone(ui.orderphone->text().toStdString(), ui.orderBrowser);
}
void AdminWidget::on_delorderconfirm_clicked()
{
	ordermanager_->delorder(ui.delorderno->text().toStdString());
}
void AdminWidget::on_back_clicked()
{
	auto adminloginwidget = new AdminLoginWidget;
	adminloginwidget->setWindowTitle("用户入口");
	adminloginwidget->show();
	delete this;
}
void AdminWidget::on_makeconclusion_clicked()
{
	ordermanager_->makeconclusion(ui.date->text().toStdString(), ui.conclusion);
}
void AdminWidget::on_reset_clicked()
{
	skumanager_->resetskubrowser(ui.skubrowser);
}
void AdminWidget::on_skufindbyname_clicked()
{
	skumanager_->skufindbyname(ui.name->text().toStdString(), ui.skubrowser);

}
void AdminWidget::on_skufindbyno_clicked()
{
	skumanager_->skufindbyno(ui.no->text().toStdString(), ui.skubrowser);
}
void AdminWidget::on_delconfirm_clicked()
{
	skumanager_->delsku(ui.delno->text().toStdString());
}
void AdminWidget::on_addconfirm_clicked()
{
	skumanager_->addsku(ui.addname->text().toStdString(), ui.addprice->text().toStdString(), ui.adddiscount->text().toStdString(), ui.warn);
}
void AdminWidget::on_alterconfirm_clicked()
{
	skumanager_->altersku(ui.alterno->text().toStdString(), ui.altername->text().toStdString(), ui.alterprice->text().toStdString(), ui.alterdiscount->text().toStdString(), ui.warn);
}
