#pragma once

#include "ui_guicoursedesign.h"

#include <QtWidgets/QWidget>


class GUICourseDesign : public QWidget
{
    Q_OBJECT

public:
    GUICourseDesign(QWidget *parent = Q_NULLPTR);
private:
    Ui::GUICourseDesignClass ui;
private slots:
    void on_AdminButton_clicked();
    void on_CustomerButton_clicked();
};