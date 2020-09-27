#include "prop.h"
#include "game.h"
#include <QDebug>
const int Prop::pic[][4] = {    {4, 8,60,53},
                                {66,8,60,53},
                                {2, 72,60,53},
                                {66,8,60,53},
                                {66,72,60,53}};
extern Game *game;
Prop::Prop(Platform *p):
    state(0),
    istouched(false)

{
    setImg(0);
    setPos(p->x() + 0.5*(p->boundingRect().width() - boundingRect().width()), p->y() - boundingRect().height()+5);
}

Prop::~Prop()
{
    game->player->removeFromGroup(this);
    scene()->removeItem(this);
    game->player->setStatus(0);
    game->player->setshootEnable(true);
    disconnect(game->timer, SIGNAL(timeout()), this, SLOT(anime()));
    qDebug() << "Delete Prop";

}

void Prop::setImg(int i)
{
    QPixmap pix(":/img/prop");
    pix = pix.copy(QRect(pic[i][0],pic[i][1],pic[i][2],pic[i][3])); // cut image
    setPixmap(pix.scaled(50,42, Qt::KeepAspectRatioByExpanding));
}

void Prop::touch()
{
    if(istouched)   return;
    game->player->setStatus(1);             // accel status
    game->player->setshootEnable(false);

    // Group prop with player
    setPos(game->player->x() + 0.5*(game->player->boundingRect().width()-boundingRect().width()),
           game->player->y() - 10);
    game->player->addToGroup(this);

    istouched = true;
    qDebug() << "Prop touch!";
    connect(game->timer, SIGNAL(timeout()), this, SLOT(anime()));
}

void Prop::anime()
{
    ++state;
    if(state < 200)
        setImg(state/5 % 4 + 1);
    else // discard prop
        delete this;
}
