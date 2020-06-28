#include "mainwindow.h"
#include "map.h"
#include <QApplication>
#include <QPushButton>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    map my;

    my.start();
    my.show();

    return a.exec();
}
