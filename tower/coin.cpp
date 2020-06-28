#include "coin.h"
#include <QPainter>
#include <QDebug>

coin::coin(int num) : COIN_NUM(num), pos(170, 250)
{
}

void coin::addcoin(int num)
{
    COIN_NUM += num;
}

void coin::consumecoin(int num)
{
    if (COIN_NUM >= num)
    {
        COIN_NUM -= num;
    }
}

void coin::setcoin(int num)
{
    COIN_NUM = num;
}

void coin::show(QPainter &qp)
{
    QFont F;
    F.setPointSize(30);
    F.setBold(true);
    F.setFamily("Helvetica");

    qp.setFont(F);
    qp.setPen("white");
    qp.drawText(pos, "COIN:" + QString::number(COIN_NUM));
}
