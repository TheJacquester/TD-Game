#include "normaltower.h"
#include "game.h"

#include "tower.h"

extern int zMax;
extern Game *game;

NormalTower::NormalTower()
{
    map = game->map;
    scene = game->scene;
    setPixmap(QPixmap(game->normalTowerPath));
    W = pixmap().width();
    H = pixmap().height();
    setOffset(-W/2,-H/1.25);
    setZValue(zMax);

    //Bullet
    setBulletDamage(2);
    bulletPixPath = ":/img/resources/fireArrow.png";
}
