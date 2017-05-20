#include "bullet.h"
#include "game.h"
#include "enemy.h"

extern int zMax;
extern Game *game;

Bullet::Bullet(Tower *p)
{
    parentTower = p;
    startPos = parentTower->pos();
    targetPos = parentTower->getTargetPoint();
    damage = parentTower->getBulletDamage();
    map = game->map;
    scene = game->scene;
    setPixmap(QPixmap(parentTower->getBulletPixPath()));
    this->setZValue(zMax);
    scene->addItem(this);
    setPos(startPos);
    setScale(2);

//draw fire line
    fireLine = QLineF(parentTower->pos(),targetPos);
    setRotation(-fireLine.angle());

    t = 0;
    connect(game->bulletTimer,SIGNAL(timeout()),this,SLOT(fireStep()));

    connect(game->bulletTimer,SIGNAL(timeout()),this,SLOT(detectEnemy()));
}

void Bullet::fireStep()
{

    qreal angle = rotation();

    qreal dy = stepSize*qSin(qDegreesToRadians(angle));
    qreal dx = stepSize*qCos(qDegreesToRadians(angle));

    distTraveled += stepSize;

    setPos(x() + dx, y() + dy);

    if (distTraveled >= fireLine.length())
        this->deleteLater();


}

void Bullet::detectEnemy()
{
    if (!game->enemies.empty()) //If game has enemies
    {
        QListIterator<Enemy*> i(game->enemies);
        while (i.hasNext()) {
            Enemy *enemy = i.next();
            qreal enemyDist = QLineF(this->pos(),enemy->pos()).length();
            if (enemyDist < enemy->collisionRadius)
            {
                qDebug() << "enemy hit";
                enemy->takeDamage(damage);
                this->deleteLater();
            }
        }
    }
}
