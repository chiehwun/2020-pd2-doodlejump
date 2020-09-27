#ifndef MONSTER_BLUE_H
#define MONSTER_BLUE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "monster.h"

class Monster_blue: public Monster
{
    Q_OBJECT
public:
    Monster_blue(int x, int y);
    ~Monster_blue();
    virtual void setImg() override;
    virtual void anime_start() override;

private:
    // For move()
    const int init_x;
    const int init_y;
    QTransform Lpos;
    QTransform Rpos;
    bool isright;
};

#endif // MONSTER_BLUE_H
