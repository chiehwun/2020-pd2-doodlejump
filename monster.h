#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "hazard.h"

class Monster: public QObject, public Hazard
{
    Q_OBJECT
public:
    Monster(int x, int y);
    ~Monster();
    void touch();
    virtual void setImg() override;

    virtual void anime_start();
    void anime_end();
    bool istouched;
    double t;

public slots:
    void anime();

private:
    // For move()
    const int init_x;
    const int init_y;
};

#endif // MONSTER_H
