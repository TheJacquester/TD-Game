#include "inteltower.h"
#include "game.h"

extern int zMax;
extern Game *game;

IntelTower::IntelTower()
{
    map = game->map;
    scene = game->scene;

    //Pixmap
    upgradePix = QPixmap(":/img/resources/intelUpgrade.png");
    setPixmap(QPixmap(game->intelTowerPath));
    W = pixmap().width();
    H = pixmap().height();
    setOffset(-W/2,-H/1.25);
    setZValue(zMax);

    //Bullet
    setBulletDamage(50);
    bulletPixPath = ":/img/resources/intelArrow.png";
    setRange(1000);

    //Price
    buyPrice = game->info->intelPrice;
    sellPrice = buyPrice / 2;
    upgradePrice = round(buyPrice * 2.5);
}

