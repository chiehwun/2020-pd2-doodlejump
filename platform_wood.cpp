#include "platform_wood.h"
#include "game.h"
#include <QDebug>
const int Platform_Wood::pic[4][4] = {  {2,146,122,30},
                                        {1,182,122,40},
                                        {1,232,122,56},
                                        {2,298,122,65}};
extern Game *game;
Platform_Wood::Platform_Wood(int x, int y):
    Platform(x,y),
    istouched(false),
    state(0),
    Y_i(y),
    g(1300.0),
    max_Vy(800.0),
    Vy(0.0),
    ty(0.0)
{
    setImg();
}

void Platform_Wood::setImg()
{
    QPixmap pix(":/img/title");
    pix = pix.copy(QRect(Platform_Wood::pic[0][0],
                         Platform_Wood::pic[0][1],
                         Platform_Wood::pic[0][2],
                         Platform_Wood::pic[0][3])); // cut image
    setPixmap(pix.scaled(80,20, Qt::KeepAspectRatio));
}



void Platform_Wood::touch()
{
    if(istouched)   return;     // prevent multiple triggering
    qDebug() << "Platform_Wood touch!";
    connect(game->timer, SIGNAL(timeout()), this, SLOT(anime()));
    istouched = true;
}

void Platform_Wood::anime()
{
    ++state;
    int i = state >= 20? 3 : state/5 % 4;
    QPixmap pix(":/img/title");
    pix = pix.copy(QRect(Platform_Wood::pic[i][0],
                         Platform_Wood::pic[i][1],
                         Platform_Wood::pic[i][2],
                         Platform_Wood::pic[i][3])); // cut image
    setPixmap(pix.scaled(80,80, Qt::KeepAspectRatio));

    // moveY
    ty += game->timer->remainingTime()*0.001;
    Vy = -max_Vy + g*ty;
    if(fabs(Vy) < max_Vy)
        setY(Y_i + 0.5*g*ty*ty);
    else
        setY(y() + 15 * (Vy > 0? 1:-1));
}
