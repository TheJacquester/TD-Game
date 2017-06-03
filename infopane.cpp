#include "infopane.h"
#include "game.h"
#include <QDebug>

extern int zMax;
extern Game *game;

InfoPane::InfoPane(QWidget *parent) : QWidget(parent)
{
    wave = game->getWave();
    lives = game->getLives();

    gridLayout = new QGridLayout;
    setLayout(gridLayout);

//Labels
    QFont font = QFont("Times",15,QFont::Bold);

    int i = 0;
    //wave
    waveText = new QLabel("Wave:",this);
    waveText->setFont(font);
    gridLayout->addWidget(waveText,i,0);

    waveVal = new QLabel(QString::number(wave),this);
    waveVal->setFont(font);
    gridLayout->addWidget(waveVal,i,1);

    //wave timeout
    ++i;
    nextWaveTimeText = new QLabel("Next Wave:",this);
    nextWaveTimeText->setFont(font);
    gridLayout->addWidget(nextWaveTimeText,i,0);

    nextWaveTimeVal = new QLabel(QString::number(game->waveTime / 1000) + "s",this);
    nextWaveTimeVal->setFont(font);
    gridLayout->addWidget(nextWaveTimeVal,i,1);

    //lives
    ++i;
    livesText = new QLabel("Lives:",this);
    livesText->setFont(font);
    gridLayout->addWidget(livesText,i,0);

    livesVal = new QLabel(QString::number(lives),this);
    livesVal->setFont(font);
    gridLayout->addWidget(livesVal,i,1);

    //gold
    ++i;
    goldText = new QLabel("Gold:",this);
    goldText->setFont(font);
    gridLayout->addWidget(goldText,i,0);

    goldVal = new QLabel(QString::number(gold),this);
    goldVal->setFont(font);
    gridLayout->addWidget(goldVal,i,1);

    //income
    ++i;
    incomeText = new QLabel("Income:",this);
    incomeText->setFont(font);
    gridLayout->addWidget(incomeText,i,0);

    incomeVal = new QLabel(QString::number(income),this);
    incomeVal->setFont(font);
    gridLayout->addWidget(incomeVal,i,1);

//Buttons
    QString butStyle = "background-color: black;"
                       "border-style: outset;"
                       "border-width: 2px;"
                       "border-radius: 5px;"
                       "border-color: beige;"
                       "font: bold 14px;"
                       "color: white;"
                       "min-width: 10em;"
                       "padding: 6px;";
    ++i;
//    spawnEnemy = new QPushButton(QIcon(QPixmap(game->smallEnemyPixmapPath).copy(0,0,10,25).scaledToWidth(200)),"Spawn Enemy",this);
    spawnEnemy = new QPushButton("Spawn Enemy",this);
    spawnEnemy->setStyleSheet(butStyle);
    gridLayout->addWidget(spawnEnemy,i,0,1,0);
    connect(spawnEnemy,SIGNAL(clicked(bool)),this,SLOT(infoSpawnEnemyClicked()));

    ++i;
    nextWave = new QPushButton("Start Next Wave",this);
    nextWave->setStyleSheet(butStyle);
    gridLayout->addWidget(nextWave,i,0,1,0);
    connect(nextWave,SIGNAL(clicked(bool)),this,SLOT(infoNextWaveClicked()));

    ++i;
    quitGame = new QPushButton("Quit Game",this);
    quitGame->setStyleSheet(butStyle);
    gridLayout->addWidget(quitGame,i,0,1,0);
    connect(quitGame,SIGNAL(clicked(bool)),game,SLOT(endGame()));
}

int InfoPane::getWave() const
{
    return wave;
}

void InfoPane::setWave(int value)
{
    wave = value;
    waveVal->setText(QString::number(wave));
    increaseGold(income);
}

int InfoPane::getLives() const
{
    return lives;
}

void InfoPane::setLives(int value)
{
    lives = value;
    livesVal->setText(QString::number(lives));
}

int InfoPane::getIncome() const
{
    return income;
}

void InfoPane::setIncome(int value)
{
    income = value;
    incomeVal->setText(QString::number(income));
}

void InfoPane::increaseIncome(int value)
{
    setIncome(income + value);
}

int InfoPane::getGold() const
{
    return gold;
}

void InfoPane::setGold(int value)
{
    gold = value;
    goldVal->setText(QString::number(gold));
    game->towerPane->setAffordableTowers(gold);
}

void InfoPane::decreaseGold(int value)
{
    setGold(gold - value);
}

void InfoPane::increaseGold(int value)
{
    setGold(gold + value);
}

void InfoPane::infoNextWaveClicked()
{
//Increase income
    increaseIncome(5);
//Force timeout to start next wave
    game->waveTimer->stop();
    QMetaObject::invokeMethod(game->waveTimer, "timeout");
}

void InfoPane::infoSpawnEnemyClicked()
{
    //Send codeword to spawn enemy for the opponent
    game->host->write(game->host->spwn);
}

void InfoPane::updateWaveTime()
{
    int waveTime = game->waveTimer->remainingTime() / 1000;
    nextWaveTimeVal->setText(QString::number(waveTime) + "s");
}
