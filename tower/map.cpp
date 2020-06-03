#include "map.h"
#include "enemy.h"
#include <QPainter>
#include <QTime>
#include <QPushButton>
#include <QDebug>

map::map(QWidget * parent):QWidget(parent),startButton("开始"){
    setStyleSheet("background-color:white;");
    resize(B_WIDTH, B_HEIGHT);

    for (int i=0;i<=ENEMY_NUM-1;i++){
        enemy _npc;
        npc.push_back(_npc);
    }
    startButton.move(1500,200);
    startButton.setParent(this);
    count=0;
    step=0;
}

void map::start(){
    connect(&startButton,&QPushButton::clicked,this,&map::init);
}

void map::init(){

    for (int i=0;i<=npc.size()-1;i++){
        npc[i].x-=(80*i);
    }

    timeID=startTimer(DELAY);
}

void map::timerEvent(QTimerEvent * e){
    Q_UNUSED(e);
    if (gameover()){
        killTimer(timeID);
    }
    else {
        npcMove();
        defenceTower.attack(npc);
        repaint();
    }
}

void map::paintEvent(QPaintEvent * e){
    Q_UNUSED(e);
    QPainter qp(this);
    npcPaint(qp);
    defenceTower.paint(qp);
}

void map::npcMove(){
    for (int i=0;i<=npc.size()-1;i++){
        npc[i].move();
    }
}

void map::npcPaint(QPainter &qp){
    for (int i=0;i<=npc.size()-1;i++){
        npc[i].paint(qp);
    }
}

bool map::gameover(){
    bool temp=true;
    for (int i=0;i<=npc.size()-1;i++){
        temp=(temp && (npc[i].dead()));
    }
    return temp;
}
