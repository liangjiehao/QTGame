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
    deployTower.move(1700,150);
    deployTower.setParent(this);
    startButton.setText("开始");
    startButton.move(1700,200);
    startButton.setParent(this);
    count=0;
    step=0;
    update();
}

void map::start(){
    connect(&deployTower,&QPushButton::clicked,this,&map::deploy);
    connect(&startButton,&QPushButton::clicked,this,&map::init);
}

void map::init(){
    if (isactive){
        killTimer(timeID);
        killTimer(timeID1);
    }
    for (int i=0;i<=npc.size()-1;i++){
        npc[i].init();
        npc[i].x-=(80*i);
    }
    home.reset();
    isactive=true;
    timeID=startTimer(DELAY);
    timeID1=startTimer(3*DELAY);
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
    //Q_UNUSED(e);

        if (gameover() || home._base<=0){
            killTimer(timeID);
            killTimer(timeID1);
            isactive=false;
            qDebug()<<timeID<<" killed";
        }
        else {
            if (e->timerId()==timeID){
                npcMove();
            }
            if (e->timerId()==timeID1){
                towerAttack();
            }
            npcAttack();
            repaint();
        }


}

void map::paintEvent(QPaintEvent * e){
    Q_UNUSED(e);
    QPainter qp(this);
    home.paint(qp);
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

void map::npcAttack(){
    for (int i=0;i<=npc.size()-1;i++){
        if (npc[i].dead() && npc[i].life>0){
            home.beAttacked(npc[i]);
            npc[i].life=0;
        }
    }
}

bool map::gameover(){
    bool temp=true;
    for (int i=0;i<=npc.size()-1;i++){
        temp=(temp && (npc[i].dead()));
    }
    return temp ;
}
