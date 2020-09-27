#include "monster.h"
#include "game.h"

extern Game *game;
Monster::Monster(int x, int y):
    Hazard::Hazard(x,y),
    istouched(false),
    t(0.0),
    init_x(x),
    init_y(y)
{
    setImg();
//    setPos(x, y);
    connect(game->timer, SIGNAL(timeout()), this, SLOT(anime()));
    qDebug() << "monster created";
}

Monster::~Monster()
{
    disconnect(game->timer, SIGNAL(timeout()), this, SLOT(anime()));
    qDebug() << "Delete monster";
    // Goto Hazard::~Hazard()
}

void Monster::setImg()
{
    QPixmap pix(":/img/title");
    pix = pix.copy(QRect(294, 529, 98,76)); // cut image
    setPixmap(pix.scaled(80,20, Qt::KeepAspectRatioByExpanding));
}

void Monster::anime()
{
    t += game->timer->remainingTime();
    if(!istouched)
        anime_start();
    else
        anime_end();
}

void Monster::touch()
{
    // prevent multiple triggering
    if(istouched) return;
    istouched = true;
    t = 0.0;
}

void Monster::anime_start()
{
    setX(init_x + 20*sin(0.01*t));
    setY(init_y + 10*sin(5 + 0.007*t));
}

void Monster::anime_end()
{
    if(t < 200)
        setY(y() + 10);
    else
        delete this;
}
