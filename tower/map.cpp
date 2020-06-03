#include "map.h"
#include "enemy.h"
#include <QPainter>
#include <QTime>
#include <QPushButton>


map::map(QWidget * parent):QWidget(parent),startButton("开始"),npc(),defenceTower(){
    setStyleSheet("background-color:white;");
    resize(B_WIDTH, B_HEIGHT);
    startButton.move(1500,200);
    startButton.setParent(this);
    count=0;
    step=0;
}

void map::start(){
    connect(&startButton,&QPushButton::clicked,this,&map::init);
}

void map::init(){
    timeID=startTimer(DELAY);
}

void map::timerEvent(QTimerEvent * e){
    Q_UNUSED(e);
    if (npc.dead()){
        killTimer(timeID);
    }
    else {
        npc.move();
        defenceTower.attack(npc);
        repaint();
    }
}

void map::paintEvent(QPaintEvent * e){
    Q_UNUSED(e);
    QPainter qp(this);
    npc.paint(qp);
    defenceTower.paint(qp);
}
