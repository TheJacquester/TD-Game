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
    background->setPixmap(QPixmap(":/img/resources/background.jpg"));
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
    grid->addItem(spacer,2,0,1,0);
}

void LoadScreen::singlePlayerBut_clicked()
{
    //New Game
    game = new Game;
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


