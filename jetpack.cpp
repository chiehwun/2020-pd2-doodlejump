#include "jetpack.h"
#include "game.h"
#include <QDebug>
const int Jetpack::pic[][4] = { {69, 257,55,124},       // not ignite
                                {5,  257,55,124},
                                {5,    1,55,124},
                                {69,   1,55,124},
                                {133,  1,55,124},
                                {197,  1,55,124},
                                {5,  129,55,124},
                                {69, 129,55,124},
                                {133,129,55,124},
                                {197,129,55,124}};
extern Game *game;
Jetpack::Jetpack(Platform *p):
    Prop(p),
    state(0),
    istouched(false)

{
    setImg(0);
    setPos(p->x() + 0.5*(p->boundingRect().width() - boundingRect().width()),
           p->y() - boundingRect().height()*0.55);
}

Jetpack::~Jetpack()
{
    qDebug() << "Delete Jetpack";
    // Goto Prop::~Prop()
}

void Jetpack::setImg(int i)
{
    QPixmap pix(":/img/jetpack");
    pix = pix.copy(QRect(Jetpack::pic[i][0],
                         Jetpack::pic[i][1],
                         Jetpack::pic[i][2],
                         Jetpack::pic[i][3])); // cut image
    setPixmap(pix.scaled(55,100, Qt::KeepAspectRatio));
}

void Jetpack::touch()
{
    if(istouched)   return;
    game->player->setStatus(1);             // accel status
    game->player->setshootEnable(false);

    // Group jetpack with player
    setPos(game->player->x() + game->player->boundingRect().width()*0.6,
           game->player->y() + 25);
    game->player->addToGroup(this);
    show();

    istouched = true;
    qDebug() << "Jetpack touch!";
    connect(game->timer, SIGNAL(timeout()), this, SLOT(anime()));
}

void Jetpack::anime()
{
    ++state;
    if(state < 200)
        setImg(state/5 % 8 + 2);
    else if(state < 400)
        setImg(game->randInt(0,1));
    else // discard jetpack
        delete this;
}
