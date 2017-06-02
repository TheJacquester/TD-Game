#ifndef MAP_H
#define MAP_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "tile.h"

class Map: public QGraphicsPixmapItem
{
public:
    Map(QGraphicsScene *s);
    Tile *getTile(int x, int y);
    int getMapW();
    int getMapH();
private:
    int mapW = 18;
    int mapH = 18;
    Tile *map[100][100];
    QGraphicsScene *scene;

    int verticalTileOffset(int x, int y);
};

#endif // MAP_H
