#pragma once
#include "ui_adminloginwidget.h"
#include <QWidget>

class AdminLoginWidget : public QWidget
{
	Q_OBJECT

public:
	AdminLoginWidget(QWidget *parent = Q_NULLPTR);
	~AdminLoginWidget();

private:
	Ui::AdminLoginWidget ui;
private slots:
	void on_login_clicked();
	void on_back_clicked();
};
