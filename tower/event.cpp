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

void map::mousePressEvent(QMouseEvent * e){
    qDebug()<<"click position:"<<e->x()<<' '<<e->y();
    if (allowDeploy && TOWER_NUM >=1){
        if (checkOverlap(e->x(),e->y())){
            tower _tow(this,e->x(),e->y(),setPower,setRange);
            defenceTower.push_back(_tow);
            QPainter qp(this);
            _tow.paint(qp);
            countDeployedTower();
        }
        else{
            allowDeploy=false;
        }
        update();
    }
}

void map::timerEvent(QTimerEvent * e){
    //Q_UNUSED(e);

        if (gameover() || home._base<=0){
            killTimer(timeID);
            killTimer(timeID1);
            isactive=false;
            //qDebug()<<timeID<<" killed";
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
        home.paint(qp);
        npcPaint(qp);
        towerPaint(qp);
    }

}
