#ifndef LOADSCREEN_H
#define LOADSCREEN_H

#include <QMainWindow>
#include <QToolButton>

#include "game.h"

class LoadScreen : public QMainWindow
{
    Q_OBJECT
public:
    explicit LoadScreen(QWidget *parent = 0);

private:
//Buttons
    QToolButton *singlePlayerBut, *hostBut, *joinBut;
    bool multiPlayerMenuOpen = false;

    QGridLayout *grid;
//Window
    int W = 250, H = 400;
    QLabel *background;
signals:

private slots:
    void singlePlayerBut_clicked();
    void hostBut_clicked();
    void joinBut_clicked();
public slots:
};

#endif // LOADSCREEN_H
