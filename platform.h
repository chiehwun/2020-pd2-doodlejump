#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>

class Platform: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    Platform(int x, int y);
    ~Platform();
    virtual void setImg();
    virtual void touch();
};

#endif // PLATFORM_H
