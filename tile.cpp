#include "tile.h"


Tile::Tile()
{

}

Tile::Tile(QString pixmapPath, int x, int y)
{
    type = GroundTile;
    setTilePixmap();
    setScale(tileScale);
    tileW = tileScale * tileW;
    tileH = tileScale * tileH;
    setOffset(-(1.1*tileW)/4,-(1.05*tileH)/4);
    //Set x and y coordinates of map
    tileX = x;
    tileY = y;
}

TileType Tile::getTileType()
{
    return type;
}

int Tile::getTileW()
{
    return tileW;
}

int Tile::getTileH()
{
    return tileH;
}

int Tile::getTilePixmapW()
{
    return tilePixmapW;
}

int Tile::getTilePixmapH()
{
    return tilePixmapH;
}

int Tile::getTileX()
{
    return tileX;
}

int Tile::getTileY()
{
    return tileY;
}

void Tile::setTileType(TileType t)
{
    type = t;
}

void Tile::setTilePixmap()
{
    QPixmap p = QPixmap(":/img/resources/tiles.png");
    int w = tilePixmapW, h = tilePixmapH;
    switch (type) {
    case PathTile:
        p = p.copy(0,0,w,h);
        setPixmap(p);
        break;
    case TowerTile:
        p = p.copy(0,0,w,h);
        setPixmap(p);
        break;
    default: GroundTile:
        p = p.copy(w,0,w,h);
        setPixmap(p);
        break;
    }
}
