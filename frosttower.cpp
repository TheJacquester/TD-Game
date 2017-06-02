#include "frosttower.h"
#include "game.h"

extern int zMax;
extern Game *game;

FrostTower::FrostTower()
{
    map = game->map;
    scene = game->scene;

    //Pixmap
    upgradePix = QPixmap(":/img/resources/frostUpgrade.png");
    setPixmap(QPixmap(game->frostTowerPath));
    W = pixmap().width();
    H = pixmap().height();
    setOffset(-W/2,-H/1.25);
    setZValue(zMax);

    //Bullet
    setBulletDamage(30);
    bulletPixPath = ":/img/resources/frostArrow.png";
    setRange(800);

    //Price
    buyPrice = game->info->frostPrice;
    sellPrice = buyPrice / 2;
    upgradePrice = round(buyPrice * 2.5);
}
