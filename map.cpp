#include <QDebug>

#include "map.h"
#include "game.h"

extern int zMax;
extern Game *game;

Map::Map(QGraphicsScene *s)
{
    mapW = game->mapW;
    mapH = game->mapH;
    int z = 0;
    scene = s;

    for (int i = mapW - 1; i >= 0; --i)
    {
        for(int j = 0; j < mapH; ++j)
        {
            map[i][j] = new Tile(":/img/resources/tiles.png",i,j);
            int tileW = map[i][j]->getTileW();
            int tileH = map[i][j]->getTileH();
            int x = (j * tileW / 2) + (i*tileW / 2);
            int y = (j * tileH / 2) - (i*tileH / 2) + mapH*tileH*.5;
//            int r = rand()%6;
            int r = verticalTileOffset(i,j);
            map[i][j]->setPos(x,y+r);
            z++;
            map[i][j]->setZValue(z);
            scene->addItem(map[i][j]);
        }
    }
    zMax = z;
}

Tile *Map::getTile(int x, int y)
{
    return map[x][y];
}

int Map::getMapW()
{
    return mapW;
}

int Map::getMapH()
{
    return mapH;
}

int Map::verticalTileOffset(int x, int y)
{
    return (-2*x*x + y*y)/3;
}
