#include "ultitower.h"
#include "game.h"

extern int zMax;
extern Game *game;

UltiTower::UltiTower()
{
    map = game->map;
    scene = game->scene;
    setPixmap(QPixmap(game->ultiTowerPath));
    W = pixmap().width();
    H = pixmap().height();
    setOffset(-W/2,-H/1.25);
    setZValue(zMax);

    //Bullet
    setBulletDamage(40);
    bulletPixPath = ":/img/resources/ultiArrow.png";
    setRange(1000);
}
