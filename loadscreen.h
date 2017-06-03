#ifndef LOADSCREEN_H
#define LOADSCREEN_H

#include <QMainWindow>
#include <QToolButton>
#include <QSpinBox>
#include <QGroupBox>

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

//Button Style
    QString butStyle;

    QGridLayout *grid;
//Window
    int W = 250, H = 400;
    QLabel *background;

//Spin Boxes
    QGridLayout *groupBoxLayout;
    QGroupBox *settingsGroupBox;
    QSpinBox *wSpinBox, *hSpinBox;

//Loading Sprite
    QTimer *timer;
    QLabel *sprite;
    QList <QPixmap> sprites;
    int spriteCount = 0;

signals:

private slots:
    void singlePlayerBut_clicked();
    void hostBut_clicked();
    void joinBut_clicked();
    void nextPixmap();
public slots:
};

#endif // LOADSCREEN_H
