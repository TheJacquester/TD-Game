#include "frosttower.h"
#include "game.h"

extern int zMax;
extern Game *game;

FrostTower::FrostTower()
{
    map = game->map;
    scene = game->scene;
    setPixmap(QPixmap(game->frostTowerPath));
    W = pixmap().width();
    H = pixmap().height();
    setOffset(-W/2,-H/1.25);
    setZValue(zMax);

    //Bullet
    setBulletDamage(5);
    bulletPixPath = ":/img/resources/frostArrow.png";
}
