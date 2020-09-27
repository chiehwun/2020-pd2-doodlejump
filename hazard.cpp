#include "hazard.h"
#include "game.h"
#include <QDebug>

extern Game *game;
Hazard::Hazard(int x, int y):
    t(0.0)
{
    setImg();
    setPos(x, y);
}

Hazard::~Hazard()
{
    scene()->removeItem(this);
    qDebug() << "Delete Hazard";
}

void Hazard::setImg()
{
    QPixmap pix(":/img/title");
    pix = pix.copy(QRect(452,100,147,133)); // cut image
    setPixmap(pix.scaled(100,100, Qt::KeepAspectRatio));
}


