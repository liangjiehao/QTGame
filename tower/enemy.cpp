#include "map.h"
#include "enemy.h"
#include <QPainter>
#include <QTime>
#include <QPushButton>
#include "enemy.h"

enemy::enemy(){
    dot.load("dot.png");
    x=400;
    y=500;
    step=20;
}

void enemy::move(){
    x+=step;
}

void enemy::paint(QPainter &qp){
    qp.drawImage(x,y,dot);
}

bool enemy::dead(){
    return x<1500 ? false :true;
}
