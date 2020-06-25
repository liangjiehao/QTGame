#ifndef COIN_H
#define COIN_H

#include <QPainter>
#include <QPoint>

class coin
{
public:
    coin(int num=200);
    void addcoin(int);
    void consumecoin(int);
    void show(QPainter &);
    void setcoin(int );
    void reset(){COIN_NUM=ORIGIN_COIN;};
    bool check_coin(int num=0){return COIN_NUM>=num ? true : false;};
private:
    int COIN_NUM=200;
    static const int ORIGIN_COIN=200;
    QPoint pos;
};

#endif // COIN_H
