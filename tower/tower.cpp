#include "tower.h"
#include <QPainter>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QWidget>
#include <QSize>
#include <QObject>
#include "map.h"
#include <QPropertyAnimation>

tower::tower(QWidget *parent, int x, int y, int _power, int _range, QString type)
    : towParent(parent), type(type), range(_range), power(_power), x(x), y(y)
{

    if (this->type == "red")
    {
        tow.load(":/new/redtow.png");
        towType = QIcon(":/new/redtow.png");
    }
    else if (this->type == "blue")
    {
        tow.load(":/new/bluetow.png");
        towType = QIcon(":/new/bluetow.png");
    }
    else
    {
        tow.load(":/new/yasuo.png");
        towType = QIcon(":/new/yasuo.png");
    }

    hasaki.setIcon(QIcon(":/new/hasaki.png"));
    hasaki.setIconSize(QSize(200, 200));
    hasaki.setParent(towParent);

    ring.setIcon(QIcon(":/new/chaojibing.png"));
    ring.setIconSize(QSize(200, 200));
    ring.setParent(towParent);

    setPosition();

    this->resize(towType.actualSize(QSize(300, 300)));
    this->setParent(towParent);
    this->setIcon(towType);
    this->setIconSize(towType.actualSize(QSize(300, 300)));
    this->move(this->x, this->y);

    updateTower.setIcon(QIcon(":/new/update.png"));
    updateTower.setParent(towParent);

    deleteTower.setIcon(QIcon(":/new/delete.png"));
    deleteTower.setParent(towParent);

    func();
}

tower::tower(const tower &T) : QPushButton(), towParent(T.towParent), range(T.range), power(T.power), x(T.x), y(T.y)
{
    tow = T.tow;
    type = T.type;
    towType = T.towType;
    singleMode = T.singleMode;

    updateTower.setIcon(QIcon(":/new/update.png"));
    updateTower.setParent(towParent);

    deleteTower.setIcon(QIcon(":/new/delete.png"));
    deleteTower.setParent(towParent);

    hasaki.setIcon(QIcon(":/new/hasaki.png"));
    hasaki.setIconSize(QSize(200, 200));
    hasaki.setParent(towParent);

    ring.setIcon(QIcon(":/new/chaojibing.png"));
    ring.setIconSize(QSize(200, 200));
    ring.setParent(towParent);

    setParent(towParent);
    setIcon(towType);
    setIconSize(towType.actualSize(QSize(100, 200)));
    move(x, y);
    func();
}

void tower::setSingleMode()
{
    singleMode = true;
}

void tower::operator=(const tower &T)
{
    tow = T.tow;
    type = T.type;
    towType = T.towType;
    towParent = T.towParent;
    range = T.range;
    power = T.power;
    x = T.x;
    y = T.y;
    singleMode = T.singleMode;

    updateTower.setIcon(QIcon(":/new/update.png"));
    updateTower.setParent(towParent);

    deleteTower.setIcon(QIcon(":/new/delete.png"));
    deleteTower.setParent(towParent);

    hasaki.setIcon(QIcon(":/new/hasaki.png"));
    hasaki.setIconSize(QSize(200, 200));
    hasaki.setParent(towParent);

    ring.setIcon(QIcon(":/new/chaojibing.png"));
    ring.setIconSize(QSize(200, 200));
    ring.setParent(towParent);

    setParent(towParent);
    setIcon(towType);
    setIconSize(towType.actualSize(QSize(100, 200)));
    move(x, y);
    func();
}

void tower::func()
{
    connect(this, &QPushButton::clicked, this, &tower::towerFunc);
    connect(&updateTower, &QPushButton::clicked, this, &tower::updateTowerFun);
    connect(&deleteTower, &QPushButton::clicked, this, &tower::deleteTowerFun);
}

void tower::setPosition()
{
    x -= (towType.actualSize(QSize(100, 200)).width() / 2 + 5);
    y -= (towType.actualSize(QSize(100, 200)).height() / 2 + 5);
}

bool tower::checkEnemy(enemy &npc, bool ai)
{
    int temp_range = range;
    if (ai)
    {
        temp_range += 50;
    }
    return (temp_range * temp_range) > ((npc.x - x) * (npc.x - x) + (npc.y - y) * (npc.y - y));
}

void tower::attack(QVector<enemy> &npc)
{

    if (type == "single")
    {
        for (int i = 0; i <= npc.size() - 1; i++)
        {
            if (!npc[i].dead() && checkEnemy(npc[i]))
            {

                hasaki.show();
                QPropertyAnimation *testAnimation = new QPropertyAnimation(&hasaki, "geo");
                testAnimation->setDuration(400);

                testAnimation->setEndValue(QRectF(npc[i].x - npc[i].getWidth(), npc[i].y - npc[i].getHeight(), 100, 100));
                testAnimation->setEndValue(QRectF(npc[i].x - npc[i].getWidth(), npc[i].y - npc[i].getHeight(), 150, 150));

                testAnimation->start();

                npc[i].damage(power);
                if (npc[i].life <= 0 && !npc[i].isKilled)
                {
                    map *mappt = dynamic_cast<map *>(towParent);
                    mappt->COIN.addcoin(npc[i].award);

                    npc[i].isKilled = true;
                }
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i <= npc.size() - 1; i++)
        {

            if (!npc[i].dead() && checkEnemy(npc[i]))
            {

                QTime time = QTime::currentTime();
                qsrand(time.msec() + time.second() * 1000);

                int n = power;
                bool ignore_defence = false;
                if (type == "blue")
                {
                    n += (qrand() % 120);
                    ignore_defence = true;
                }

                if ((qrand() % 20) == 1 && type == "red")
                {
                    n = npc[i].life;
                    ignore_defence = true;
                }

                npc[i].damage(n, ignore_defence);
                if (npc[i].life <= 0 && !npc[i].isKilled)
                {
                    map *mappt = dynamic_cast<map *>(towParent);
                    mappt->COIN.addcoin(npc[i].award);

                    npc[i].isKilled = true;
                }
            }
        }
    }
}

void tower::paint(QPainter &qp)
{

    Q_UNUSED(qp)
    QPushButton::show();
}

void tower::paint(QPainter &qp, QVector<enemy> &npc)
{

    QPushButton::show();

    QPen pen;
    if (type == "single")
    {
        return;
    }
    else
    {
        pen.setColor(type);
    }

    pen.setWidthF(2);
    qp.setPen(pen);

    for (int i = 0; i <= npc.size() - 1; i++)
    {
        if (!npc[i].dead() && checkEnemy(npc[i]))
        {

            qp.drawLine(npc[i].x + npc[i].getWidth() / 2, npc[i].y + npc[i].getHeight() / 2, x + 20, y + 40);
            if (type == "single")
            {
                break;
            }
        }
    }
}

void tower::showDeployRange(QPainter &qp, int range)
{

    QPen pen;
    pen.setColor("red");
    pen.setWidth(4);
    qp.setPen(pen);

    qp.drawEllipse(x - range, y - range, 2 * range, 2 * range);
}

void tower::towerFunc()
{
    if (funcControl)
    {
        updateTower.setParent(towParent);
        updateTower.setIconSize(QSize(50, 50));
        if (type == "single")
        {
            updateTower.move(x - 60, y - 20);
        }
        else
        {
            updateTower.move(x + 60, y - 20);
        }

        updateTower.show();

        deleteTower.setParent(towParent);
        deleteTower.setIconSize(QSize(50, 50));
        if (type == "single")
        {
            deleteTower.move(x - 60, y + 20);
        }
        else
        {
            deleteTower.move(x + 60, y + 20);
        }

        deleteTower.show();

        funcControl = false;
    }
    else
    {
        updateTower.hide();
        deleteTower.hide();
        funcControl = true;
    }
}

void tower::updateTowerFun()
{
    this->power *= 1.2;
    this->range += 50;
    map *mappt = dynamic_cast<map *>(towParent);
    mappt->COIN.consumecoin(100 * updateWeight);
    mappt->update();
    updateWeight *= 2;
}

void tower::deleteTowerFun()
{
    map *mappt = dynamic_cast<map *>(towParent);
    deletedMark = true;
    mappt->deleteTower();
    mappt->update();
}
