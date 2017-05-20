#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>
#include <QPointF>
#include <QtMath>
#include <QList>
#include <QListIterator>

#include "map.h"

class PathFinder
{
public:
    PathFinder(Map *m,QGraphicsScene *s);
//    QList <QPointF> calcPath();
    QList <Tile*> calcPath();
private:
    int mapW, mapH;
    QGraphicsScene *scene;
    Map *map;
    Tile *start, *finish;
    QList<Tile *> openList;
    QList<Tile *> closedList;

    int calcH(Tile *a, Tile *b);
    void calcNeighbours(Tile *n);
    Tile *smallestF();
    void printMap();
};

#endif // PATHFINDER_H
