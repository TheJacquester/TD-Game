#include "pathfinder.h"

PathFinder::PathFinder(Map *m, QGraphicsScene *s)
{
    map = m;
    mapW = map->getMapW();
    mapH = map->getMapH();
    //initializes start and finish tiles
    start = map->getTile(0,0);
    finish = map->getTile(mapW-1,mapH-1);
    //Temp******
    QPixmap p = QPixmap(":/img/resources/tiles.png");
    p = p.copy(start->getTilePixmapW()*2,0,start->getTilePixmapW(),start->getTilePixmapH());
    start->setPixmap(p);
    finish->setPixmap(p);
    //Temp******
    scene = s;
}

QList<Tile *> PathFinder::calcPath()
{
    QList <Tile*> path;
    closedList.append(start);
    calcNeighbours(start);

    for (int x = 0; x < mapW; ++x)
    {
        for(int y = 0; y < mapH; ++y) //Bou van agter af vorentoe
        {
                map->getTile(x,y)->path = false;
        }
    }

    while (openList.length() > 0)
    {
        Tile *t = smallestF();
        closedList.append(t);
        if (t == finish)
        {
            while (t->parent)
            {
                t->path = true;
                path.prepend(t);
                t = t->parent;
            }
        }
        calcNeighbours(t);
    }

    printMap();
    path.prepend(start);
    return path; //return a path of points for the enemy
}

int PathFinder::calcH(Tile *a, Tile *b)
{
    int x, y;
    int ax = a->getTileX(),ay = a->getTileY();
    int bx = b->getTileX(),by = b->getTileY();
    ax - bx >= 0 ? x = ax - bx : x = bx - ax; // ander manier vir if
    ay - by >= 0 ? y = ay - by : y = by - ay; // het dan nie abs nodig nie
    return x >= y ? x * 10: y * 10; // : is else kondisie
}

void PathFinder::calcNeighbours(Tile *n)
{
    for (int dy = -1; dy <= 1; ++dy)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            int x = dx + n->getTileX();
            int y = dy + n->getTileY();
            Tile *currentTile = new Tile();
            currentTile = map->getTile(x,y);
            if ((x >=0) && (x < mapW) &&  /*x en y positief && in map?*/
                (y >=0) && (y < mapH) &&
                !openList.contains(currentTile) &&    /*Neighbour Tile nie in openList && closedList nie?*/
                !closedList.contains(currentTile) &&
                (currentTile->getTileType() == GroundTile) &&  /*Neighbour Tile bekostigbaar?*/
                ((dx*dx) || (dy*dy)) &&/*nie op current Tile?*/
                (dx*dx) != (dy*dy))
            {
                currentTile->parent = n;
                if ((dx*dx)&&(dy*dy)) //^2 om nie te toets vir negatief ook nie
                    currentTile->g = n->g + 14;
                else
                    currentTile->g = n->g + 10;
                currentTile->h = calcH(currentTile, finish);
                currentTile->f = currentTile->g + currentTile->h;
                openList.append(currentTile);
            }
        }
    }
}

Tile *PathFinder::smallestF()
{
    Tile *r = openList.first();
    QListIterator <Tile *> i(openList);
    while (i.hasNext())
    {
        Tile *t = i.next();
        if (t->f < r->f)
            r = t;
    }
    openList.removeOne(r); // Kan binary heap gebruik om dit te optimeer
    return r;
}

void PathFinder::printMap()
{
    QPixmap pathPix, groundPix = QPixmap(":/img/resources/tiles.png");
    pathPix = groundPix.copy(0,0,start->getTilePixmapW(),start->getTilePixmapH());
    groundPix = groundPix.copy(start->getTilePixmapW(),0,start->getTilePixmapW(),start->getTilePixmapH());

    for (int x = 0; x < mapW; ++x)
    {
        for(int y = 0; y < mapH; ++y) //Build from back to front
        {
            if (map->getTile(x,y)->path)
                map->getTile(x,y)->setPixmap(pathPix);
            else
                map->getTile(x,y)->setPixmap(groundPix);

        }
    }
}
