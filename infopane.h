#ifndef INFOPANE_H
#define INFOPANE_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>

class InfoPane : public QWidget
{
    Q_OBJECT
public:
    explicit InfoPane(QWidget *parent = 0);

    int getWave() const;
    void setWave(int value);

    int getLives() const;
    void setLives(int value);

    QPushButton *spawnEnemy, *nextWave;

    int getIncome() const;
    void setIncome(int value);
    void increaseIncome(int value);

    int getGold() const;
    void setGold(int value);
    void decreaseGold(int value);
    void increaseGold(int value);

private:
    int wave, lives;
    int income = 3;
    int gold = 50;
    QLabel *waveText, *livesText, *incomeText,
            *goldText, *nextWaveTimeText;
    QLabel *waveVal, *livesVal, *incomeVal,
            *goldVal, *nextWaveTimeVal;
    QGridLayout *gridLayout;

signals:

public slots:
    void infoNextWaveClicked();
    void infoSpawnEnemyClicked();
    void updateWaveTime();
};

#endif // INFOPANE_H
