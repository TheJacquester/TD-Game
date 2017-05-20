#ifndef TOWERPANE_H
#define TOWERPANE_H

#include <QObject>
#include <QWidget>
#include <QToolButton>
#include <QGridLayout>
#include <QLabel>

#include "normaltower.h"
#include "frosttower.h"
#include "inteltower.h"
#include "ultitower.h"

class TowerPane : public QWidget
{
    Q_OBJECT
public:
    explicit TowerPane(QWidget *parent = 0);
    QGridLayout *towerButLayout;
    void setTowerPaneEnabled(bool b);

    void setAffordableTowers(int gold); //enable only affordable towers
private:
//Labels And Buttons
    QToolButton *normalTowerBut, *frostTowerBut, *intelTowerBut, *ultiTowerBut;
    QLabel *lblNormal, *lblFrost, *lblIntel, *lblUlti;
    void initLabels();
//Towers
    //If Tower does not name a type occur:
    //  move the #include to cpp instead of h (circular referencing)
    //  run qmake
    NormalTower* normalTower;
    FrostTower* frostTower;
    IntelTower* intelTower;
    UltiTower* ultiTower;

//Tower costs
    int normalPrice = 10;
    int frostPrice = 40;
    int intelPrice = 80;
    int ultiPrice = 150;
    const qreal towerScaleFactor = 0.5; //Tower Scale Factor on Button

signals:

public slots:
    void normalTowerBut_clicked();
    void frostTowerBut_clicked();
    void intelTowerBut_clicked();
    void ultiTowerBut_clicked();

};

#endif // TOWERPANE_H
