#include "platform.h"
#include <QDebug>

Platform::Platform(int x, int y)
{
    setImg();
    setPos(x, y);
}

Platform::~Platform()
{
    scene()->removeItem(this);
//    qDebug() << "Delete Platform";
}

void Platform::setImg()
{
    QPixmap pix(":/img/title");
    pix = pix.copy(QRect(0,0,120,35)); // cut image
    setPixmap(pix.scaled(80,24, Qt::KeepAspectRatio));
}

void Platform::touch()
{
//    qDebug() << "Platform touch!";
    return;
}
