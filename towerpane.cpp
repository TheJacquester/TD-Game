#include "towerpane.h"
#include "game.h"

extern Game *game;

TowerPane::TowerPane(QWidget *parent) : QWidget(parent)
{

//Tower costs
    normalPrice = game->info->normalPrice;
    frostPrice = game->info->frostPrice;
    intelPrice = game->info->intelPrice;
    ultiPrice = game->info->ultiPrice;

//tower labels
    initLabels();

//tower buttons
    const QSize towerButSize = QSize(150,100);
    normalTowerBut = new QToolButton(this);
    normalTowerBut->setMinimumSize(towerButSize);
    normalTowerBut->setIcon(QIcon(game->normalTowerPath));
    normalTowerBut->setIconSize(towerButSize);

    frostTowerBut = new QToolButton(this);
    frostTowerBut->setMinimumSize(towerButSize);
    frostTowerBut->setIcon(QIcon(game->frostTowerPath));
    frostTowerBut->setIconSize(towerButSize);

    intelTowerBut = new QToolButton(this);
    intelTowerBut->setMinimumSize(towerButSize);
    intelTowerBut->setIcon(QIcon(game->intelTowerPath));
    intelTowerBut->setIconSize(towerButSize);

    ultiTowerBut = new QToolButton(this);
    ultiTowerBut->setMinimumSize(towerButSize);
    ultiTowerBut->setIcon(QIcon(game->ultiTowerPath));
    ultiTowerBut->setIconSize(towerButSize);

//grid
    towerButLayout = new QGridLayout;

    //labels
    towerButLayout->addWidget(lblNormal,0,0,Qt::AlignCenter);
    towerButLayout->addWidget(lblFrost,0,1,Qt::AlignCenter);
    towerButLayout->addWidget(lblIntel,0,2,Qt::AlignCenter);
    towerButLayout->addWidget(lblUlti,0,3,Qt::AlignCenter);

    //buttons
    towerButLayout->addWidget(normalTowerBut,1,0,Qt::AlignCenter);
    towerButLayout->addWidget(frostTowerBut,1,1,Qt::AlignCenter);
    towerButLayout->addWidget(intelTowerBut,1,2,Qt::AlignCenter);
    towerButLayout->addWidget(ultiTowerBut,1,3,Qt::AlignCenter);

//signals
    connect(normalTowerBut,SIGNAL(clicked(bool)),SLOT(normalTowerBut_clicked()));
    connect(frostTowerBut,SIGNAL(clicked(bool)),SLOT(frostTowerBut_clicked()));
    connect(intelTowerBut,SIGNAL(clicked(bool)),SLOT(intelTowerBut_clicked()));
    connect(ultiTowerBut,SIGNAL(clicked(bool)),SLOT(ultiTowerBut_clicked()));
}

void TowerPane::setTowerPaneEnabled(bool b)
{
    normalTowerBut->setEnabled(b);
    frostTowerBut->setEnabled(b);
    intelTowerBut->setEnabled(b);
    ultiTowerBut->setEnabled(b);
}

void TowerPane::setAffordableTowers(int gold)
{
    if (!game->waveActive)
    {
        setTowerPaneEnabled(false);
        if(gold >= normalPrice)
            normalTowerBut->setEnabled(true);
        if(gold >= frostPrice)
            frostTowerBut->setEnabled(true);
        if(gold >= intelPrice)
            intelTowerBut->setEnabled(true);
        if(gold >= ultiPrice)
            ultiTowerBut->setEnabled(true);
    }
}

void TowerPane::initLabels()
{
    QFont font = QFont("Times",10,QFont::Bold);

    lblNormal = new QLabel("Archer Tower - " +QString::number(normalPrice) +" Gold",this);
    lblNormal->setFont(font);

    lblFrost = new QLabel("Frost Tower - " +QString::number(frostPrice) +" Gold",this);
    lblFrost->setFont(font);

    lblIntel = new QLabel("Intel Tower - " +QString::number(intelPrice) +" Gold",this);
    lblIntel->setFont(font);

    lblUlti = new QLabel("Ulti Tower - " +QString::number(ultiPrice) +" Gold",this);
    lblUlti->setFont(font);
}

void TowerPane::normalTowerBut_clicked()
{
    normalTower = new NormalTower();
    normalTower->setScale(towerScaleFactor);
    game->scene->addItem(normalTower);
    normalTower->grabMouse(); //NB! for mouseTracking!! Use after placing item
    game->info->decreaseGold(normalPrice);
}

void TowerPane::frostTowerBut_clicked()
{
    frostTower = new FrostTower();
    frostTower->setScale(towerScaleFactor);
    game->scene->addItem(frostTower);
    frostTower->grabMouse(); //NB! for mouseTracking!! Use after placing item
    game->info->decreaseGold(frostPrice);
}

void TowerPane::intelTowerBut_clicked()
{
    intelTower = new IntelTower();
    intelTower->setScale(towerScaleFactor);
    game->scene->addItem(intelTower);
    intelTower->grabMouse(); //NB! for mouseTracking!! Use after placing item
    game->info->decreaseGold(intelPrice);
}

void TowerPane::ultiTowerBut_clicked()
{
    ultiTower = new UltiTower();
    ultiTower->setScale(towerScaleFactor);
    game->scene->addItem(ultiTower);
    ultiTower->grabMouse(); //NB! for mouseTracking!! Use after placing item
    game->info->decreaseGold(ultiPrice);
}
