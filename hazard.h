#ifndef HAZARD_H
#define HAZARD_H
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QRect>
#include <QGraphicsScene>

class Hazard: public QGraphicsPixmapItem
{
public:
    Hazard(int x, int y);
    ~Hazard();
    virtual void setImg();
    double t;
};

#endif // HAZARD_H
