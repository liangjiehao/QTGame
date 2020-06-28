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


    if (allowDeploy && TOWER_NUM >=1){

        if (checkOverlap(e->x(),e->y()) && COIN.check_coin(currentTowerCost)){
            tower _tow(this,e->x(),e->y(),setPower,setRange,currentTowerType);
            defenceTower.push_back(_tow);

            COIN.consumecoin(currentTowerCost);
            QPainter qp(this);

            countDeployedTower();
            towerControl="";
            setCursor(Qt::ArrowCursor);
        }

        update();
    }
    else{
        setCursor(Qt::ArrowCursor);

    }
}

void map::timerEvent(QTimerEvent * e){

        if (gameover() && home._base>0){
            victory.raise();
            QTimer::singleShot(800,&victory,&QPushButton::show);

            reStart.hide();
            deployTower.hide();
            deployTowerHigh.hide();
            deployTowerhasaki.hide();
            startButton.hide();
            recycle.hide();


            killTimer(timeID);
            killTimer(timeID1);
            isactive=false;

        }
        else if (home._base<=0){
            defeat.raise();
            QTimer::singleShot(800,&defeat,&QPushButton::show);

            reStart.hide();
            deployTower.hide();
            deployTowerHigh.hide();
            deployTowerhasaki.hide();
            startButton.hide();
            recycle.hide();

            killTimer(timeID);
            killTimer(timeID1);
            isactive=false;
        }
        else {
            if (e->timerId()==timeID){
                npcMove(defenceTower);

            }
            if (e->timerId()==timeID1){
                towerAttack();

            }
            npcAttack();

            update();
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
        COIN.show(qp);
        home.paint(qp);
        npcPaint(qp);
        towerPaint(qp);
    }
    if (towerControl == "showTowerRange"){
        showTowerRange(qp);
    }

}
