#include "map.h"
#include "enemy.h"
#include <QPainter>
#include <QTime>
#include <QPushButton>
#include "enemy.h"
#include <QDebug>
#include <QVector2D>
#include <QMatrix>
#include <math.h>
#include <QTime>

enemy::enemy(int life, int defence, int attack, int type) : QPushButton()
{
    if (type == 0)
    {
        dot.load(":/new/xiaobing.png");
        step = 20;
        aiEnemy = false;
        rage = false;
        award = 5;
    }
    else if (type == 1)
    {
        dot.load(":/new/chaojibing1.png");
        step = 20;
        aiEnemy = false;
        rage = false;
        award = 10;
    }
    else if (type == 2)
    {
        dot.load(":/new/rider.png");
        step = 50;
        aiEnemy = true;
        rage = false;
        award = 25;
    }
    else if (type == 3)
    {
        QTime time = QTime::currentTime();
        qsrand(time.msec() + time.second() * 1000);
        if (qrand() % 5 == 0)
        {
            dot.load(":/new/zhaoxin.png");
            award = 80;
        }
        else
        {
            dot.load(":/new/diana.png");
            award = 20;
        }

        step = 40;
        aiEnemy = false;
        rage = false;
    }

    this->life = life;
    this->defence = defence;
    this->attack = attack;

    x = _X - dot.width() / 2;
    y = _Y - dot.height() / 2;

    count_step = 0;

    makePathPoint();
    makePathDirection();
}

enemy::enemy(const enemy &p) : QPushButton()
{
    x = p.x;
    y = p.y;
    step = p.step;
    dot = p.dot;
    life = p.life;
    defence = p.defence;
    attack = p.attack;
    aiEnemy = p.aiEnemy;
    rage = p.rage;
    award = p.award;
    path_point = p.path_point;
    path_direction = p.path_direction;
    count_step = p.count_step;
}

void enemy::operator=(const enemy &p)
{
    x = p.x;
    y = p.y;
    step = p.step;
    dot = p.dot;
    life = p.life;
    defence = p.defence;
    attack = p.attack;
    aiEnemy = p.aiEnemy;
    rage = p.rage;
    award = p.award;
    path_point = p.path_point;
    path_direction = p.path_direction;
    count_step = p.count_step;
}

void enemy::init()
{
    dot.load(":/new/chaojibing.png");
    x = _X;
    y = _Y;
    step = 20;
    life = LIFE;
}

void enemy::move(QVector<tower> &T)
{
    QVector2D direct = QVector2D(QPoint(X, Y) - QPoint(x + dot.width() / 2, y + dot.height() / 2));

    if (direct.length() < 20)
    {
        return;
    }

    if (rage || direct.length() < 300 || x >= X || y >= Y || x < -50 || y < -50)
    {
        rage = true;
        direct.normalize();
        x += direct.x() * step;
        y += direct.y() * step;
        return;
    }

    for (int i = 0; i <= T.size() - 1; i++)
    {

        if (T[i].checkEnemy(*this, true))
        {
            direct = QVector2D(QPoint(x, y) - QPoint(T[i].getX(), T[i].getY())).normalized() + QVector2D(QPoint(X, Y) - QPoint(x, y)).normalized();
            direct.normalize();
            x += direct.x() * step;
            y += direct.y() * step;
            return;
        }
    }
    direct.normalize();
    x += direct.x() * step;
    y += direct.y() * step;
}

void enemy::move()
{

    if (count_step < path_direction.size())
    {
        x += path_direction[count_step].x() * step;
        y += path_direction[count_step].y() * step;
        count_step++;
    }
}

void enemy::paint(QPainter &qp)
{
    if (!dead())
    {

        qp.drawImage(x, y, dot);
        QFont F;
        F.setPointSize(10);
        QPointF p;

        p.setX(x);
        p.setY(y - 2);
        if (life <= 1000)
        {
            qp.setPen("red");
        }
        else
        {
            qp.setPen("white");
        }
        qp.setFont(F);
        qp.drawText(p, QString::number(life));
    }
}

bool enemy::dead()
{

    if ((life <= 0) || (abs(x + dot.width() / 2 - X) < step && abs(y + dot.height() / 2 - Y) < step))
    {
        return true;
    }
    else
        return false;
}

void enemy::damage(int power, bool ignoredefence)
{

    if (step == 40 && power > 380)
    {
        return;
    }

    if (ignoredefence)
    {
        life -= power;
    }
    else
    {
        life -= (power * (1 - defence / 1000.0));
    }
}

void enemy::makePathPoint(int type)
{
    path_point.clear();
    if (type == 0)
    {
        path_point.append(QPoint(_X, _Y));
        path_point.append(QPoint(1564, 64));
        path_point.append(QPoint(1564, 314));
        path_point.append(QPoint(609, 314));
        path_point.append(QPoint(609, 934));
        path_point.append(QPoint(89, 934));
        path_point.append(QPoint(89, 472));
        path_point.append(QPoint(1010, 472));
        path_point.append(QPoint(X, Y));
    }
}

void enemy::makePathDirection()
{
    path_direction.clear();

    for (int i = 0; i <= path_point.size() - 2; i++)
    {
        QVector2D direct(path_point[i + 1] - path_point[i]);

        double step_num = (direct.length()) / ((direct.normalized().length() * step));

        direct.normalize();
        for (int j = 0; j <= step_num; j++)
        {
            path_direction.append(direct);
        }
    }
}
