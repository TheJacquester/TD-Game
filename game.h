#ifndef GAME_H
#define GAME_H
#include <QMainWindow>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QToolButton>
#include <QLabel>
#include <QDebug>
#include <QObject>
#include <QList>
#include <QMouseEvent>
#include <QTimer>
#include <QSound>

#include "tower.h"
#include "normaltower.h"
#include "frosttower.h"
#include "inteltower.h"
#include "ultitower.h"
#include "tile.h"
#include "map.h"
#include "enemy.h"
#include "pathfinder.h"
#include "infopane.h"
#include "udpsocket.h"
#include "towerpane.h"

class Game:  public QMainWindow
{
    Q_OBJECT //Run qmake after including this!
public:
    Game();
    void loadInterface();
    void startGame();
    void hostMode();
    void joinMode();
    void singlePlayerMode();
    void gameOver();

//Game info
    void decreaseLives();
    QLabel *gameOverLabel;
    QPushButton *resetBut;

//Layout
    QGridLayout *outerLayout, *optionsLayout;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QWidget *mainWidget; //Custom CentralWidget
    const int minSceneW = 600; //Min Playable Map Size
    const int minSceneH = 500;

    InfoPane *info;
    TowerPane *towerPane;

//Map and path finding
    void setMapSize(int w, int h);
    int mapW = 15;
    int mapH = 15;
    Map *map;
    PathFinder *pathFinder;
    QList <Tile*> path;

//Enemy
    void spawnEnemy();
    void initEnemyPixmap();
    QList <QPixmap> largeEnemySprites, smallEnemySprites;
    QList <Enemy*> enemies;
    int maxEnemies = 10;
    int spawnCount = 0;
    int healtMax = 800;

//Image Paths
    //Towers
    QString normalTowerPath = ":/img/resources/normal.png";
    QString frostTowerPath = ":/img/resources/frost.png";
    QString intelTowerPath = ":/img/resources/intel.png";
    QString ultiTowerPath = ":/img/resources/ulti.png";
    //Enemies
    QString largeEnemyPixmapPath = ":/img/resources/superGreen.png";
    QString smallEnemyPixmapPath = ":/img/resources/smallGreen.png";
    //Tile
    QString tilePixmapPath = ":/img/resources/tiles.png";

//Scene Background
    QString backgroundPath = ":/img/resources/gameBackground.jpg";
    void initZoom();
    QToolButton *zoomInBut, *zoomOutBut;

//Networking
    UdpSocket *host;
    void initHost();
    bool opponentConnected;

//Timing
    QTimer *startGameTimer,*timer, *bulletTimer, *fireTimer,
            *waveTimer, *spawnTimer, *secTimer;
    int gameSpeed = 50; //Game step speed (msec)
    int waveTime = 20000;
    int spawnTime = 500;
    int startGamePollTime = 500;
    int getLives() const;
    void setLives(int value);

//waves
    bool waveActive = false; //True if ememies on map
    void waveStart(); //Disable buttons for next wave
    void waveStop(); //Enable buttons after wave
    int getWave() const;
    void setWave(int value);
    bool firstWave = true; //first wave should take longer to spawn

private:
    void initTowerBut();
    void initInfo();
    void initTimers();

//game info
    int wave = 1;
    int lives = 1;

private slots:
    void nextWave();
    void spawnWaveEnemies(); //Check if max enemies reached and spawn
    void ckeckStartGame(); //Check if game is ready to be started
    void zoomIn();
    void zoomOut();
public slots:
    void endGame(); //Calls resetGame() from main
};

#endif // GAME_H
