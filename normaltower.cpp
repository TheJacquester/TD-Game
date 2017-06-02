#include "normaltower.h"
#include "game.h"

#include "tower.h"

extern int zMax;
extern Game *game;

NormalTower::NormalTower()
{
    map = game->map;
    scene = game->scene;

    //Pixmap
    upgradePix = QPixmap(":/img/resources/normalUpgrade.png");
    setPixmap(QPixmap(game->normalTowerPath));
    W = pixmap().width();
    H = pixmap().height();
    setOffset(-W/2,-H/1.25);
    setZValue(zMax);

    //Bullet
    setBulletDamage(20);
    bulletPixPath = ":/img/resources/fireArrow.png";
    setRange(800);

    //Price
    buyPrice = game->info->normalPrice;
    sellPrice = buyPrice / 2;
    upgradePrice = round(buyPrice);
}
