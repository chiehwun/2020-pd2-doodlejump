#include "monster_blue.h"
#include "game.h"

extern Game *game;
Monster_blue::Monster_blue(int x, int y):
    Monster::Monster(x,y),
    init_x(x),
    init_y(y),
    isright(true)
{
    Lpos.scale(1,1);
    Rpos.scale(-1,1).translate(-boundingRect().width(), 0);
    setImg();
    setTransform(Lpos);
////  already  connect at Monster::Monster(), if added => double frequency
//    connect(game->timer, SIGNAL(timeout()), this, SLOT(anime()));
    qDebug() << "blue monster created";
}

Monster_blue::~Monster_blue()
{
    qDebug() << "Delete blue monster";
}

void Monster_blue::setImg()
{
    QPixmap pix(":/img/title");
    pix = pix.copy(QRect(129, 373, 75,99)); // cut image
    setPixmap(pix.scaled(60,20, Qt::KeepAspectRatioByExpanding));
}

void Monster_blue::anime_start()
{
    // X: wandering
    if(x() >= game->scene->width() - boundingRect().width() && isright) {
        isright = false;
        setTransform(Rpos);
    }
    else if(x() <= 0 && !isright) {
        isright = true;
        setTransform(Lpos);
    }
    setX(x()+ (isright? 4:-4));

    // Y: trembling
    setY(init_y + 10*sin(5 + 0.005*t));
}
