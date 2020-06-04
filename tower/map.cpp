#include "map.h"
#include "enemy.h"
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QDebug>
#include <QMouseEvent>

map::map(QWidget * parent):QWidget(parent){
    setStyleSheet("background-color:white;");
    resize(B_WIDTH, B_HEIGHT);

    for (int i=0;i<=ENEMY_NUM-1;i++){
        enemy _npc;
        npc.push_back(_npc);
    }
    deployTower.setText("部署防御塔");
    deployTower.move(1500,150);
    deployTower.setParent(this);
    startButton.setText("开始");
    startButton.move(1500,200);
    startButton.setParent(this);
    count=0;
    step=0;
}

void map::start(){
    connect(&deployTower,&QPushButton::clicked,this,&map::deploy);
    connect(&startButton,&QPushButton::clicked,this,&map::init);
}

void map::init(){
    if (isactive){
        killTimer(timeID);
    }
    for (int i=0;i<=npc.size()-1;i++){
        npc[i].init();
        npc[i].x-=(80*i);
    }
    isactive=true;
    timeID=startTimer(DELAY);
}

void map::deploy(){
    qDebug()<<"tower deployed!"<<endl;
    allowDeploy=true;
}

void map::countDeployedTower(){
    TOWER_NUM--;
    allowDeploy=false;
}
void map::mousePressEvent(QMouseEvent * e){
    if (allowDeploy && TOWER_NUM >=1){
        tower _tow(e->x(),e->y());
        defenceTower.push_back(_tow);
        QPainter qp(this);
        _tow.paint(qp);
        countDeployedTower();
        update();
    }

    //qDebug()<<e->x()<<" "<<e->y();
}

void map::timerEvent(QTimerEvent * e){
    Q_UNUSED(e);
    if (gameover()){
        killTimer(timeID);
        isactive=false;
        qDebug()<<timeID<<" killed";
    }
    else {
        npcMove();
        towerAttack();
        repaint();
    }
}

void map::paintEvent(QPaintEvent * e){
    Q_UNUSED(e);
    QPainter qp(this);
    npcPaint(qp);
    towerPaint(qp);
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

void map::towerAttack(){
    for (int i=0;i<=defenceTower.size()-1;i++){
        defenceTower[i].attack(npc);
    }
}

void map::towerPaint(QPainter & qp){
    for (int i=0;i<=defenceTower.size()-1;i++){
        defenceTower[i].paint(qp,npc);
    }
}

bool map::gameover(){
    bool temp=true;
    for (int i=0;i<=npc.size()-1;i++){
        temp=(temp && (npc[i].dead()));
    }
    return temp;
}
