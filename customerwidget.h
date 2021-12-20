#pragma once
#include "ui_customerwidget.h"
#include <QWidget>
#include<string>
class CustomerWidget : public QWidget
{
	Q_OBJECT

public:
	CustomerWidget(int customerno, std::string phone,QWidget *parent = Q_NULLPTR);
	~CustomerWidget();
private:
	Ui::CustomerWidget ui;
	std::string phone_;
	int customerno_;
private slots:
	void on_refreshmenu_clicked();
	void on_addtocart_clicked();
	void on_clearcart_clicked();
	void on_makedineorder_clicked();
	void on_back_clicked();
	void on_makedeliverorder_clicked();
};
