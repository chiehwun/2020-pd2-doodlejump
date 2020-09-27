#include "bullet.h"
#include <QDebug>
#include "game.h"
#include "monster.h"

extern Game *game;
Bullet::Bullet()
{
    QPixmap pix(":/img/bullet");
    pix = pix.copy(QRect(0,0,25,25));
    setPixmap(pix);
    connect(game->timer, SIGNAL(timeout()), this, SLOT(move()));
    setPos(game->player->x() + (game->player->boundingRect().width() - boundingRect().width())*0.5, game->player->y());
    qDebug() << "bullet created";
}

Bullet::~Bullet()
{
    scene()->removeItem(this);
    qDebug() << "Delete bullet";
}

void Bullet::move()
{
    setY(y() - 30);
    if(y() < game->offsetY) {
        delete this;
    }
    else {
        // Blast monster
        QList<QGraphicsItem *> col_items = collidingItems();
        for(auto coll = col_items.begin(); coll < col_items.end(); ++coll) {
            if(Monster *m = dynamic_cast<Monster *>(*coll)) {
                delete m;
                delete this;
                return;
            }
        }
    }
}
