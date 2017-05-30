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
    void printMap(); //Print map with Path tiles
};

#endif // PATHFINDER_H
