#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>
#include <QPointF>
#include <QLine>
#include <QtMath>
#include <QTimer>
#include <QObject>

#include "map.h"
#include "tower.h"

class Bullet: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(Tower *p);
private:
    int damage;
    Tower *parentTower;
    QPointF startPos, targetPos;
    QGraphicsScene *scene;
    Map *map;

//fire line
    const int stepSize = 15;
    int distTraveled = 0;
    qreal t = 0; //parameterized point on path line
    QLineF fireLine;
public slots:
    void fireStep();
    void detectEnemy();
};

#endif // BULLET_H
