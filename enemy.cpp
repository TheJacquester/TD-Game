#include "enemy.h"
#include "game.h"

extern int zMax;
extern Game *game;

Enemy::Enemy()
{
    healthMax = game->healtMax;
    map = game->map;
    scene = game->scene;
    path = game->path;

//Pixmap
    setPixmap(game->enemySprites.at(0));//QPixmap(game->enemyPixmapPath));
    setScale(10);
    W = pixmap().width();
    H = pixmap().height();
    setOffset(-W/2,-H/1.25);
    setZValue(path.at(0)->zValue());
    setPos(path.first()->pos());

    //set first linear path between points
    qreal x1 = path.at(0)->x(), y1 = path.at(0)->y();
    qreal x2 = path.at(1)->x(), y2 = path.at(1)->y();
    l.setLine(x1,y1,x2,y2);
    t = 0; //starting parameterized position on line

//health
    health = healthMax;
    healthBarMax = W*0.8;
    healthBarHeight = H*0.1;
    healthBar = new QGraphicsRectItem(-healthBarMax/2,-H*0.9,healthBarMax,healthBarHeight,this);
    healthBar->setBrush(QBrush(Qt::red));
    healthBar->setZValue(this->zValue());
    healthBar->show();

}

Enemy::~Enemy()
{
    game->enemies.removeOne(this);
    if (game->enemies.isEmpty())
        game->waveStop();
}

void Enemy::takeDamage(int damage)
{
    health -= damage;
    updateHealtBar();
    if (health <= 0)
    {
        this->deleteLater();
        game->enemies.removeOne(this);
        game->info->increaseGold(gold);
    }
}

void Enemy::updateHealtBar()
{
    healthBar->setRect(-healthBarMax/2,-H*0.9,((qreal)health/healthMax)*healthBarMax,healthBarHeight);
}

void Enemy::setHopSkipMax(int value)
{
    hopSkipMax = value;
}

void Enemy::hop()
{
    if(spriteCount <= 9)
        spriteCount++;
    else
        spriteCount = 0;
    setPixmap(game->enemySprites.at(spriteCount));
    if (hopSkipCount == hopSkipMax)
    {
        hopSkipCount = 0;
        t += stepSize;
        if (t >= 1)
        {
            pathPos++;

            if (pathPos >= path.size() - 1) //if end tile reached
            {
                this->deleteLater();
                game->decreaseLives();
            }
            else
            {
                qreal x1 = path.at(pathPos)->x(), y1 = path.at(pathPos)->y();
                qreal x2 = path.at(pathPos+1)->x(), y2 = path.at(pathPos+1)->y();

                l.setLine(x1,y1,x2,y2);
                t = 0.0;
            }
        }
        else
        {
            setPos(l.pointAt(t));
            setZValue(path.at(pathPos)->zValue()+1);
                //+1 To let enemies walk behind towers, but in front of tiles
        }
    }
    else hopSkipCount++;
}
