#include "mainwindow.h"
#include "map.h"
#include <QApplication>
#include <QPushButton>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    map my;
    //QPushButton tower("开始",&my);
    my.show();
    my.start();
    //enemy::connect(&tower,SIGNAL(clicked),&my,SLOT(init));
    return a.exec();
}
