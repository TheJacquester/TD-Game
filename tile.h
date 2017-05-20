#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include <QtEvents>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

enum TileType
{
    GroundTile,
    TowerTile
};

class Tile: public QGraphicsPixmapItem
{
public:
    Tile();
    Tile(QString pixmapPath, int x, int y);
    TileType getTileType();
    int getTileW();
    int getTileH();
    int getTilePixmapW();
    int getTilePixmapH();
    int getTileX();
    int getTileY();
    void setTileType(TileType t);

    int f,g,h;
    Tile *parent = 0;
    bool path = false;

private:
    TileType type;
    static int const tilePixmapW = 64;
    static int const tilePixmapH = 32;
    static int const tileScale = 2;
    int tileW = 64;
    int tileH = 32;
    int tileX;
    int tileY;
};

#endif // TILE_H
