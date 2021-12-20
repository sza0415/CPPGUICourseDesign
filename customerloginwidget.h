#pragma once
#include "ui_customerloginwidget.h"

#include <QWidget>

class CustomerLoginWidget : public QWidget
{
	Q_OBJECT

public:
	CustomerLoginWidget(QWidget *parent = Q_NULLPTR);
	~CustomerLoginWidget();
	void setphone(std::string phone);
	void setcustomerno(int customerno);	
	std::string getphone();
	int getcustomerno();
private:
	Ui::CustomerLoginWidget ui;
	std::string phone_ = "-1";
	int customerno_ = -1;
private slots:
	void on_login_clicked();
	void on_back_clicked();
};
