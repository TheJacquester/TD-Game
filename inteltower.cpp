#include "inteltower.h"
#include "game.h"

extern int zMax;
extern Game *game;

IntelTower::IntelTower()
{
    map = game->map;
    scene = game->scene;
    setPixmap(QPixmap(game->intelTowerPath));
    W = pixmap().width();
    H = pixmap().height();
    setOffset(-W/2,-H/1.25);
    setZValue(zMax);

    //Bullet
    setBulletDamage(30);
    bulletPixPath = ":/img/resources/intelArrow.png";
    setRange(1000);
}
