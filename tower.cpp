#include "tower.h"
#include "game.h"
#include "bullet.h"

extern int zMax;
extern Game *game;

Tower::Tower()
{
}

void Tower::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    if (!placed)
    {
        qreal d1 = dist(e->scenePos(),map->getTile(0,0)->scenePos());
        Tile *closestTile = new Tile;
        int mapW = map->getMapW();
        int mapH = map->getMapH();
        for(int x = 0;x < mapW; ++x)
        {
            for(int y = 0;y < mapH; ++y)
            {
                qreal d2 = dist(e->scenePos(),map->getTile(x,y)->scenePos());
                if(d2 <= d1)
                {
                    d1 = d2;
                    closestTile = map->getTile(x,y);
                }
            }
        }
        this->setPos(closestTile->scenePos());
    }
}

void Tower::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if(e->button() == Qt::MiddleButton && !upgraded && game->info->getGold() >= upgradePrice)
    {
        setPixmap(upgradePix);
        game->info->decreaseGold(upgradePrice);
        bulletDamage *= 2;
        upgraded = true;
    }
    if(e->button() == Qt::RightButton) //Delete Tower
    {
        currentTile->setTileType(GroundTile);
        game->info->increaseGold(sellPrice);
        deleteLater();
    }
    if (!placed)
    {
        qreal d1 = dist(e->scenePos(),map->getTile(0,0)->scenePos());
        Tile *closestTile = new Tile;
        int mapW = map->getMapW();
        int mapH = map->getMapH();
        for(int x = 0;x < mapW; ++x)
        {
            for(int y = 0;y < mapH; ++y)
            {
                qreal d2 = dist(e->scenePos(),map->getTile(x,y)->scenePos());
                if(d2 <= d1)
                {
                    d1 = d2;
                    closestTile = map->getTile(x,y);
                    currentTile = closestTile;
                }
            }
        }
        if (closestTile->getTileType() == GroundTile)
        {
            closestTile->setTileType(TowerTile);
            if (placable())
            {
                this->setPos(closestTile->scenePos());
                this->setZValue(closestTile->zValue()+1);
                //+1 To let enemies walk behind towers, but in front of tiles
                placed = true;
                ungrabMouse();
            }
            else
            {
                closestTile->setTileType(GroundTile);
                game->pathFinder->calcPath();
            }
        }
    }
}

qreal Tower::dist(QPointF p1, QPointF p2)
{
    return qPow(p1.x() - p2.x(),2) + qPow(p1.y() - p2.y(),2);
}

QPointF Tower::getTargetPoint() const
{
    return targetPoint;
}

void Tower::setTargetPoint(const QPointF &value)
{
    targetPoint = value;
}

int Tower::getBulletDamage() const
{
    return bulletDamage;
}

void Tower::setBulletDamage(int value)
{
    bulletDamage = value;
}

void Tower::setRange(qreal r)
{
    range = r;
    connect(game->fireTimer,SIGNAL(timeout()),this,SLOT(setTarget()));
}

bool Tower::placable()
{
    game->pathFinder = new PathFinder(map,scene); //Possible place for stack overflow
    QList <Tile*> path = game->pathFinder->calcPath();
    if (path.size()<=1)
        return false;
    else
        return true;
}

QString Tower::getBulletPixPath() const
{
    return bulletPixPath;
}

void Tower::setBulletPixPath(const QString &value)
{
    bulletPixPath = value;
}

void Tower::setTarget()
{
    if (!game->enemies.empty()) //If game has enemies
    {
        QListIterator<Enemy*> i(game->enemies);
        qreal closestDist = range/2;
        while (i.hasNext()) {
            target = i.next();
            qreal enemyDist = QLineF(this->pos(),target->pos()).length();
            if (enemyDist < closestDist)
            {
                closestDist = enemyDist;
                targetAcquired = true;
                qreal enemyDist = QLineF(this->pos(),target->pos()).length();
                if (enemyDist < range/2) fire();
                else targetAcquired = false;
            }
        }
    }
}

void Tower::fire()
{
    targetPoint = target->pos();
    new Bullet(this); //Risky code for living on the edge
}

