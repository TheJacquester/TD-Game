#include "game.h"

#include <QApplication>
#include <QDesktopWidget>
extern int zMax;
extern void resetGame();

Game::Game()
{

}

void Game::loadInterface()
{
//Place game window in the center of the screen
    move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    this->setWindowTitle("Legion TD");
//Custom CentralWidget for QMainWindow Requirements
    mainWidget = new QWidget;
    setCentralWidget(mainWidget);
    mainWidget->setMouseTracking(true);
    setMouseTracking(true);

//Layout
    outerLayout = new QGridLayout(this);
    initTowerBut();

//Graphics Scene and View
    scene = new QGraphicsScene(this);
//    scene->setBackgroundBrush(QBrush(QPixmap::fromImage(QImage(backgroundPath))));
    view = new QGraphicsView(scene);
    view->setMinimumSize(minSceneW,minSceneH);
    view->setMouseTracking(true);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//Graphics View and Column properties
    outerLayout->addWidget(view,0,0);
    outerLayout->setColumnStretch(0,10);
    outerLayout->setRowStretch(0,10);
    outerLayout->setRowStretch(1,0);

    mainWidget->setLayout(outerLayout);
    view->show();
    view->scale(0.5,0.5);

//Tower Buttons and Options
    initInfo();

//Map
    map = new Map(scene);

//Timing
    initTimers();
}

void Game::startGame()
{
//    towerPane->setTowerPaneEnabled(true);
    towerPane->setAffordableTowers(info->getGold());
    timer->start();
    bulletTimer->start();
    fireTimer->start();
    waveTimer->start();
    secTimer->start();
}

void Game::hostMode()
{
    loadInterface();
    show();
    opponentConnected = false;
    initHost();
    startGameTimer->start();
}

void Game::joinMode()
{
    loadInterface();
    show();
    startGame();
}

void Game::singlePlayerMode()
{
    loadInterface();
    show();
    startGame();
    info->spawnEnemy->hide();
}

void Game::gameOver()
{
    timer->stop();
    bulletTimer->stop();
    fireTimer->stop();
    waveTimer->stop();
    spawnTimer->stop();

    gameOverLabel = new QLabel(this);
    gameOverLabel->setPixmap(QPixmap(":/img/resources/gameOver.png"));
    int lblW = gameOverLabel->pixmap()->width();
    int lblH = gameOverLabel->pixmap()->height();
    gameOverLabel->setMinimumSize(lblW,lblH);
    gameOverLabel->move(width()/2 - lblW/2,height()/2 - lblH);
    gameOverLabel->show();

    resetBut = new QPushButton(this);
    resetBut->setText("Reset Game");
    int btnW = resetBut->width();
    int btnH = resetBut->height();
    resetBut->move(this->width()/2 - btnW/2, gameOverLabel->y() + lblH - btnH);
    resetBut->show();

    connect(resetBut,SIGNAL(clicked(bool)),this,SLOT(endGame()));

    view->setEnabled(false);
    towerPane->setTowerPaneEnabled(false);
    info->setEnabled(false);
}

void Game::decreaseLives()
{
    if (--lives <= 0)
    {
        qDebug() << "game over";
        gameOver();
    }

    info->setLives(lives);
}

void Game::spawnEnemy()
{
    pathFinder = new PathFinder(map,scene);
    path = pathFinder->calcPath(); //calculate path and return a path of points

    Enemy *e = new Enemy();
    enemies.append(e);
    connect(timer,SIGNAL(timeout()),e,SLOT(hop()));
    scene->addItem(enemies.last());
}

void Game::initHost()
{
    host = new UdpSocket(this);
}

void Game::initTowerBut()
{
    towerPane = new TowerPane(this);
    outerLayout->addLayout(towerPane->towerButLayout,1,0);
    towerPane->setTowerPaneEnabled(false);
}

void Game::initInfo()
{
    info = new InfoPane(this);
    outerLayout->addWidget(info,0,1,0,1);
    info->show();
}

void Game::initTimers()
{
    timer = new QTimer();
    timer->setInterval(gameSpeed);

    bulletTimer = new QTimer();
    bulletTimer->setInterval(gameSpeed - 30);

    fireTimer = new QTimer();
    fireTimer->setInterval(gameSpeed*5);

    waveTimer = new QTimer();
    waveTimer->setInterval(waveTime);
    connect(waveTimer,SIGNAL(timeout()),this,SLOT(nextWave()));

    spawnTimer = new QTimer();
    spawnTimer->setInterval(spawnTime);
    connect(spawnTimer,SIGNAL(timeout()),this,SLOT(spawnWaveEnemies()));

    startGameTimer = new QTimer(this);
    startGameTimer->setInterval(startGamePollTime);
    connect(startGameTimer,SIGNAL(timeout()),this,SLOT(ckeckStartGame()));

    secTimer = new QTimer(this);
    secTimer->setInterval(1000);
    connect(secTimer,SIGNAL(timeout()),info,SLOT(updateWaveTime()));
}

void Game::endGame()
{
    this->deleteLater();
    resetGame();
}

int Game::getWave() const
{
    return wave;
}

void Game::setWave(int value)
{
    wave = value;
}

int Game::getLives() const
{
    return lives;
}

void Game::setLives(int value)
{
    lives = value;
}

void Game::nextWave()
{
    if (firstWave)
    {
        firstWave = false;
        spawnTimer->start();
    }
    else
    {
        wave++;
        maxEnemies++;
        healtMax += 60;
        spawnCount = 0;
        info->setWave(wave);
    }
}

void Game::spawnWaveEnemies()
{
    if (spawnCount < maxEnemies)
    {
        spawnEnemy();
        spawnCount++;
    }
}

void Game::ckeckStartGame()
{
    if (opponentConnected)
    {
        qDebug() << "Opponent connected";
        startGame();
        startGameTimer->deleteLater();
    }
}