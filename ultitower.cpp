#include "ultitower.h"
#include "game.h"

extern int zMax;
extern Game *game;

UltiTower::UltiTower()
{
    map = game->map;
    scene = game->scene;

    //Pixmap
    upgradePix = QPixmap(":/img/resources/ultiUpgrade.png");
    setPixmap(QPixmap(game->ultiTowerPath));
    W = pixmap().width();
    H = pixmap().height();
    setOffset(-W/2,-H/1.25);
    setZValue(zMax);

    //Bullet
    setBulletDamage(100);
    bulletPixPath = ":/img/resources/ultiArrow.png";
    setRange(1000);

    //Price
    buyPrice = game->info->ultiPrice;
    sellPrice = buyPrice / 2;
    upgradePrice = round(buyPrice * 2.5);
}
