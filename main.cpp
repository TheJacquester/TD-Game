//Alle eer aan God wie my by tye
//ondersteun het deur die rowwe prak!

#include <QApplication>
#include "loadscreen.h"

extern void resetGame();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    resetGame();

    return a.exec();
}

extern void resetGame()
{
    LoadScreen *loadScreen = new LoadScreen;
    loadScreen->show();
}
