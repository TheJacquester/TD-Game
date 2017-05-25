#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>
#include <QPointF>
#include <QtMath>
#include <QList>
#include <QListIterator>
#include <QObject>
#include <QTimeLine>
#include <QTimer>
#include <QGraphicsRectItem>

#include "map.h"
class Enemy: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy();
    ~Enemy();
    qreal collisionRadius = 70; //collision radius
    void takeDamage(int damage);
    void setHopSkipMax(int value);

private:
    //properties
    int W, H; //width and height of enemy pixmap
    int pathPos = 0;
    int healthMax;
    int health = 0;
    int gold = 2;

//visual
    int spriteCount = 0;
    QGraphicsRectItem *healthBar;
    qreal healthBarMax, healthBarHeight = 5;
    void updateHealtBar();

//linear movement
    qreal t = 0; //parameterized point on path line
    const qreal stepSize = 0.15;
    QLineF l; //line between points of enemy path
    int hopSkipMax = 0; //Controls enemy speed
    int hopSkipCount = 0;

//map
    Tile *currentTile;
    QList <Tile*> path;
    QGraphicsScene *scene;
    Map *map;
public slots:
    void hop();

};

#endif // ENEMY_H
