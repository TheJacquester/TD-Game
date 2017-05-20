#include "tile.h"


Tile::Tile()
{

}

Tile::Tile(QString pixmapPath, int x, int y)
{
    QPixmap p = QPixmap(":/img/resources/tiles.png");
    p = p.copy(tilePixmapW,0,tilePixmapW,tilePixmapH);
    setPixmap(p);
    setScale(tileScale);
    tileW = tileScale * tilePixmapW;
    tileH = tileScale * tilePixmapH;
    this->setOffset(-tileW/4,-tileH/4);
    type = GroundTile;
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
