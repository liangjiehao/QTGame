#include "coin.h"
#include <QPainter>
#include <QDebug>

coin::coin(int num):COIN_NUM(num),pos(1650,100){

}

void coin::addcoin(int num){
    COIN_NUM+=num;
}

void coin::consumecoin(int num){
    COIN_NUM-=num;
}

void coin::setcoin(int num){
    COIN_NUM=num;
}

void coin::show(QPainter & qp){
    QFont F;
    F.setPointSize(20);
    qp.setFont(F);

    qp.drawText(pos,QString::number(COIN_NUM));
    //qDebug()<<"show coin";
}
