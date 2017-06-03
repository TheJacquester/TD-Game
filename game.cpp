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
    setStyleSheet("background-color: black;"
               "border-style: outset;"
               "border-width: 2px;"
               "border-radius: 5px;"
               "border-color: beige;"
               "font: bold 14px;"
               "color: white;"
               "padding: 6px;");
    this->setWindowTitle("Legion TD");
    showFullScreen();
//Custom CentralWidget for QMainWindow Requirements
    mainWidget = new QWidget;
    setCentralWidget(mainWidget);
    mainWidget->setMouseTracking(true);
    setMouseTracking(true);

//Layout
    outerLayout = new QGridLayout(this);

//Graphics Scene and View
    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(QImage(backgroundPath)));
    view = new QGraphicsView(scene);
    view->setMinimumSize(minSceneW,minSceneH);
    view->setMouseTracking(true);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setDragMode(QGraphicsView::ScrollHandDrag);

//Graphics View and Column properties
    outerLayout->addWidget(view,0,0);
    outerLayout->setColumnStretch(0,10);
    outerLayout->setRowStretch(0,10);
    outerLayout->setRowStretch(1,0);

    mainWidget->setLayout(outerLayout);
    view->show();
    view->scale(0.3,0.3);

    initZoom();

//Tower Buttons and Options
    initInfo();
    initTowerBut();

//Map
    map = new Map(scene);

//Timing
    initTimers();

//Enemies
    initEnemyPixmap();

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
//    QSound::play("C:/Users/Jacques/Documents/Desktop/TD Game/Legion_TD_V10/resources/oboe.wav");
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
    timer->stop(); //Main Game timer (e.g. arrow steps)
    bulletTimer->stop();
    fireTimer->stop();
    waveTimer->stop();
    spawnTimer->stop();

    gameOverLabel = new QLabel(this);
    gameOverLabel->setStyleSheet("background-color: white;"
                                "border-style: outset;"
                                "border-width: 2px;"
                                "border-radius: 5px;"
                                "border-color: beige;"
                                "font: bold 14px;"
                                "color: white;"
                                "padding: 6px;");
    gameOverLabel->setPixmap(QPixmap(":/img/resources/gameOver.png"));
    int lblW = gameOverLabel->pixmap()->width();
    int lblH = gameOverLabel->pixmap()->height();
    gameOverLabel->setMinimumSize(lblW,lblH);
    gameOverLabel->move(width()/2 - lblW/2,height()/2 - lblH);
    gameOverLabel->show();

    resetBut = new QPushButton(this);
    resetBut->setText("Quit Game");
    int btnW = resetBut->width();
    int btnH = resetBut->height();
    resetBut->move(this->width()/2 - btnW/2, gameOverLabel->y() + lblH - btnH*1.5);
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

void Game::setMapSize(int w, int h)
{
    mapW = w;
    mapH = h;
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

void Game::initEnemyPixmap()
{
    QPixmap p = QPixmap(largeEnemyPixmapPath);
    int w = 25, h = 25;
    for(int i = 0; i <= 10; ++i )
        largeEnemySprites.append(p.copy(i*w,0,w,h));

    p = QPixmap(smallEnemyPixmapPath);
    w = 13;
    h = 25;
    for(int i = 0; i <= 10; ++i )
        smallEnemySprites.append(p.copy(i*w,0,w,h));
}

void Game::initZoom()
{
    QString butStyle = "background-color: black;"
                       "border-style: outset;"
                       "border-width: 2px;"
                       "border-radius: 5px;"
                       "border-color: beige;"
                       "font: bold 14px;"
                       "color: white;"
                       "padding: 6px;";
    //zoom Buttons
        const QSize zoomButSize = QSize(30,30);
        zoomInBut = new QToolButton(this);
        zoomInBut->setStyleSheet(butStyle);
        zoomInBut->setMinimumSize(zoomButSize);
        zoomInBut->setMaximumSize(zoomButSize);
        zoomInBut->setText("+");
        zoomInBut->move(20,20);
        zoomInBut->show();
        connect(zoomInBut,SIGNAL(clicked(bool)),this,SLOT(zoomIn()));

        zoomOutBut = new QToolButton(this);
        zoomOutBut->setStyleSheet(butStyle);
        zoomOutBut->setMinimumSize(zoomButSize);
        zoomOutBut->setMaximumSize(zoomButSize);
        zoomOutBut->setText("-");
        zoomOutBut->move(25+zoomOutBut->height(),20);
        zoomOutBut->show();
        connect(zoomOutBut,SIGNAL(clicked(bool)),this,SLOT(zoomOut()));

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

void Game::waveStart()
{
    towerPane->setTowerPaneEnabled(false);
    info->nextWave->setEnabled(false);
    info->quitGame->setEnabled(false);
    waveActive = true;
    waveTimer->stop();
}

void Game::waveStop()
{
    waveActive = false;
    towerPane->setAffordableTowers(info->getGold());
    info->nextWave->setEnabled(true);
    info->quitGame->setEnabled(true);
    waveTimer->start();
}

void Game::nextWave()
{
    if (firstWave)
    {
        firstWave = false;
        spawnTimer->start();
        waveStart();
    }
    else
    {
        wave++;
        maxEnemies++;
        healtMax += 60;
        spawnCount = 0;
        info->setWave(wave);
        waveStart();
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

void Game::zoomIn()
{
    view->scale(1.1,1.1);
}

void Game::zoomOut()
{
    view->scale(0.9,0.9);
}
