#include "tower.h"
#include <QPainter>

tower::tower(){
    tow.load("tow.jpg");
    x=800;
    y=200;
}

bool tower::checkEnemy(enemy & npc){
    return (range*range)>((npc.x-x)*(npc.x-x)+(npc.y-y)*(npc.y-y));
}

void tower::attack(enemy & npc){
    if (checkEnemy(npc)){
        npc.damage(power);
    }
}

void tower::paint(QPainter &qp){
    qp.drawImage(x,y,tow);
}
