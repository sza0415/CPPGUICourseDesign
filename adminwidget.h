#pragma once
#include "ui_adminwidget.h"
#include <QWidget>
#include "managerclass.h"
class AdminWidget : public QWidget
{
	Q_OBJECT

public:
	AdminWidget(QWidget *parent = Q_NULLPTR);
	~AdminWidget();
private:
	OrderManager* ordermanager_=new OrderManager;
	SkuManager* skumanager_ = new SkuManager;
	Ui::AdminWidget ui;
private slots:
	void on_getdateorder_clicked();
	void on_reset_clicked();
	void on_skufindbyname_clicked();
	void on_skufindbyno_clicked();
	void on_orderfindbyno_clicked();
	void on_orderfindbyphone_clicked();
	void on_delconfirm_clicked();
	void on_addconfirm_clicked();
	void on_alterconfirm_clicked();
	void on_delorderconfirm_clicked();
	void on_back_clicked();
	void on_makeconclusion_clicked();
};
