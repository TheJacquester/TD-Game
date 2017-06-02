#include "loadscreen.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QInputDialog>
#include <QDir>
#include <QSpacerItem>
#include <QStyle>

int zMax = 1;
Game *game;

LoadScreen::LoadScreen(QWidget *parent) : QMainWindow(parent)
{
    //Background
    background = new QLabel(this);
    background->setPixmap(QPixmap(":/img/resources/loadBackground.png"));
    background->show();
    W = background->pixmap()->width();
    H = background->pixmap()->height();
    background->setMinimumSize(W,H);

    //Constrain Window Size
    this->setMinimumSize(W,H);
    this->setMaximumSize(W,H);

    //Title
    this->setWindowTitle("Legion TD");

    //Central Widget
    QWidget *mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    //Layout
    grid = new QGridLayout(this);
    mainWidget->setLayout(grid);

    //Buttons
    singlePlayerBut = new QToolButton(this);
    singlePlayerBut->setMinimumSize(W - 20,30);
    grid->addWidget(singlePlayerBut,0,0,1,0,Qt::AlignHCenter);
    singlePlayerBut->setText("Single Player");
    singlePlayerBut->show();
    connect(singlePlayerBut,SIGNAL(clicked(bool)),this,SLOT(singlePlayerBut_clicked()));

    hostBut = new QToolButton(this);
    hostBut->setMinimumSize(W/2 - 13,30);
    grid->addWidget(hostBut,1,0,Qt::AlignLeft);
    hostBut->setText("Host Game");
    hostBut->show();
    connect(hostBut,SIGNAL(clicked(bool)),this,SLOT(hostBut_clicked()));

    joinBut = new QToolButton(this);
    joinBut->setMinimumSize(W/2 - 13,30);
    grid->addWidget(joinBut,1,1,Qt::AlignRight);
    joinBut->setText("Join Game");
    joinBut->show();
    connect(joinBut,SIGNAL(clicked(bool)),this,SLOT(joinBut_clicked()));

    QSpacerItem *spacer = new QSpacerItem(W,H - 50);
    grid->addItem(spacer,3,0,1,0);

    //Group Box
    settingsGroupBox = new QGroupBox("Game Settings",this);
    settingsGroupBox->setPalette(QPalette(Qt::black));
    grid->addWidget(settingsGroupBox,2,0,1,0,Qt::AlignCenter);
    groupBoxLayout = new QGridLayout(this);
    settingsGroupBox->setLayout(groupBoxLayout);


    //Spin Boxes and Labels
    QLabel *mapSizeLabel = new QLabel("Map Size:",this);
    groupBoxLayout->addWidget(mapSizeLabel,0,0);

    wSpinBox = new QSpinBox(this);
    wSpinBox->setPalette(QPalette(Qt::black));
    wSpinBox->setValue(10);
    wSpinBox->setMinimum(5);
    wSpinBox->setMaximum(50);
    wSpinBox->setMinimumWidth(50);
    groupBoxLayout->addWidget(wSpinBox,1,0);

    QLabel *xLabel = new QLabel("x",this);
    groupBoxLayout->addWidget(xLabel,1,1);

    hSpinBox = new QSpinBox(this);
    hSpinBox->setPalette(QPalette(Qt::black));
    hSpinBox->setValue(10);
    hSpinBox->setMinimum(5);
    hSpinBox->setMaximum(50);
    hSpinBox->setMinimumWidth(50);
    groupBoxLayout->addWidget(hSpinBox,1,2);

    //Loading Sprite
    sprite = new QLabel(this);

    QPixmap p = QPixmap(":/img/resources/superGreen.png");
    int w = 25, h = 25;
    for(int i = 0; i <= 10; ++i )
    {
        sprites.append(p.copy(i*w,0,w,h));
    }

    sprite->setPixmap(QPixmap(sprites.first()));
    sprite->move(-this->width()*3,this->height()/2);
    sprite->show();
    sprite->setMinimumSize(150,150);

    timer = new QTimer(this);
    timer->setInterval(100);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextPixmap()));
    timer->start();
}

void LoadScreen::singlePlayerBut_clicked()
{
    //New Game
    game = new Game;
    game->setMapSize(wSpinBox->value(),hSpinBox->value());
    game->singlePlayerMode();
    this->deleteLater();
}

void LoadScreen::hostBut_clicked()
{
    qDebug() << "host game";
    game = new Game;
    game->hostMode();
    this->deleteLater();
}

void LoadScreen::joinBut_clicked()
{
    bool ok;
    QString IP = QInputDialog::getText(this,"Join game","Host IP:",
                                       QLineEdit::Normal,"10.0.0.7",&ok);
    if(ok && !IP.isEmpty())
    {
        game = new Game;
//Network
        game->initHost();
        game->host->setOpponentIP(QHostAddress(IP));
        game->host->writeACK();

        game->joinMode();
//        qDebug() << "Join game with host IP: " << IP;

        this->deleteLater();
    }

}

void LoadScreen::nextPixmap()
{
    if(spriteCount <= 9)
        spriteCount++;
    else
        spriteCount = 0;
    sprite->setPixmap(sprites.at(spriteCount).scaled(sprite->minimumSize()));
    if(sprite->x() >= this->width())
        sprite->move(-this->width()*3,sprite->y());
    else
        sprite->move(sprite->x()+20,sprite->y());
}


