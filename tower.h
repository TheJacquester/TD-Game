#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>
#include <QPointF>
#include <QtMath>
#include <QList>
#include <QObject>

#include "map.h"
#include "enemy.h"

class Tower: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Tower();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e);
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void fire();

    QPointF getTargetPoint() const;
    void setTargetPoint(const QPointF &value);

    int getBulletDamage() const;
    void setBulletDamage(int value);

    QString getBulletPixPath() const;
    void setBulletPixPath(const QString &value);

protected:
    int W, H;
    int bulletDamage;
    qreal range;
    Enemy *target;
    bool targetAcquired = false;
    QGraphicsEllipseItem *fireArea;
    QGraphicsScene *scene;
    Map *map;

    qreal dist(QPointF p1, QPointF p2);
    QPointF targetPoint;

    void setRange(qreal r);
    bool placable(); //checks if tower will block path

    QString bulletPixPath;

public slots:
    void setTarget();
};

#endif // TOWER_H
