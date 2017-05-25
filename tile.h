#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include <QtEvents>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

enum TileType
{
    GroundTile,
    PathTile,
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
    void setTilePixmap();

    int f,g,h;
    Tile *parent = 0;
    bool path = false;

private:
    TileType type;
    static int const tilePixmapW = 100; //64
    static int const tilePixmapH = 166; //32
    qreal const tileScale = 1.8;
    int tileW = 100;
    int tileH = 60;
    int tileX;
    int tileY;
};

#endif // TILE_H
