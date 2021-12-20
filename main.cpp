#include"global.h"
#include "guicoursedesign.h"
#include <QtWidgets/QApplication>
#pragma execution_character_set("utf-8")
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GUICourseDesign w;
    w.show();
    return a.exec();
}
