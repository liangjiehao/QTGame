#include "map.h"
#include "enemy.h"
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QDebug>
#include <QMouseEvent>
#include <QImage>
#include <QIcon>
#include <QSize>
#include <QDebug>
#include <Qt>
#include <QPropertyAnimation>


void map::mousePressEvent(QMouseEvent * e){
    //qDebug()<<"click position:"<<e->x()<<' '<<e->y();

    if (allowDeploy && TOWER_NUM >=1){

        if (checkOverlap(e->x(),e->y()) && COIN.check_coin(currentTowerCost)){
            tower _tow(this,e->x(),e->y(),setPower,setRange,currentTowerType);
            defenceTower.push_back(_tow);
            //qDebug()<<defenceTower.size();
            //buyTower();
            COIN.consumecoin(currentTowerCost);
            QPainter qp(this);
            //_tow.paint(qp);
            //defenceTower.back();
            countDeployedTower();
            towerControl="";
            setCursor(Qt::ArrowCursor);
        }
        /*
        else{
            allowDeploy=false;
        }
        */
        update();
    }
    else{
        setCursor(Qt::ArrowCursor);
        //QCursor
    }
}

void map::timerEvent(QTimerEvent * e){
    //Q_UNUSED(e);
            //qDebug()<<home._base;
        if (gameover()){
            victory.show();
            killTimer(timeID);
            killTimer(timeID1);
            isactive=false;
            //qDebug()<<timeID<<" killed";
        }
        else if (home._base<=0){
            defeat.show();
            killTimer(timeID);
            killTimer(timeID1);
            isactive=false;
        }
        else {
            if (e->timerId()==timeID){
                npcMove();

            }
            if (e->timerId()==timeID1){
                towerAttack();
                //npcAttack();
            }
            npcAttack();
            //qDebug()<<npc.size();
            repaint();
        }
        //qDebug()<<npc.size();


}

void map::paintEvent(QPaintEvent * e){
    Q_UNUSED(e);
    QPainter qp(this);
    if (pageControl == "main"){
        drawBackGround(qp,BG);
    }
    else if (pageControl == "rule"){
        drawBackGround(qp,BG);
    }
    else if (pageControl == "selectChapter" ){
        drawBackGround(qp,BG);
    }
    else {
        drawBackGround(qp,BG);
        COIN.show(qp);
        home.paint(qp);
        npcPaint(qp);
        towerPaint(qp);
    }
    npcAward();
    if (towerControl == "showTowerRange"){
        showTowerRange(qp);
    }

}
