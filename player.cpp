#include "player.h"
#include "game.h"
#include "platform.h"
#include "platform_wood.h"
#include "hazard.h"
#include "prop.h"
#include "jetpack.h"
#include "monster.h"

const double Player::max_Vy = 900.0;
extern Game *game;
Player::Player():
    Y_i(550.0),   // 500.0
    ispause(false),
    LkeyLongPress(false),
    RkeyLongPress(false),
    Tx(400),    //400
    max_Vx(15),
    tx(0),
    g(1300.0),
    Vy(-max_Vy),
    V0y(Vy),
    ty(0.0),
    page(0),
    shoot_angle(1000),   // not shoot
    t_shoot(0),
    KeyEnable(true),
    shootEnable(true),
    status(0)
{
    // Image Initialization
        // 1. body
    pix_doodle = new QGraphicsPixmapItem();
    QPixmap pix(":/img/player_left0");
    pix_doodle->setPixmap(pix.scaled(100,100, Qt::KeepAspectRatio));
    pix_doodle->setPos(0,0);
    addToGroup(pix_doodle);
    setZValue(std::numeric_limits<qreal>::max());   // Ensure player is at the toppest
        // 2. mouth
    pix_shoot  = new QGraphicsPixmapItem();
    pix.load(":/img/player_mouth");
    pix_shoot->setPixmap(pix.scaled(100,100, Qt::KeepAspectRatio));
    pix_shoot->setPos((pix_doodle->boundingRect().width() - pix_shoot->boundingRect().width())*0.5,0);
    addToGroup(pix_shoot);
    pix_shoot->hide();
        // 3. Accel items...

    // QTransform Initialize
    Lpos.scale(1,1);
    Rpos.scale(-1,1).translate(-100, 0);

    // timer settings
    connect(game->timer, SIGNAL(timeout()), this, SLOT(move()));
    game->timer->start(20);

    // media
    playersound = new QMediaPlayer();
    playersound->setMedia(QUrl("qrc:/sound/shoot"));
}

Player::~Player()
{
    qDebug() << "~Player()";
    KeyEnable = false;
    game->timer->stop();
    disconnect(game->timer, SIGNAL(timeout()), this, SLOT(move()));
    removeFromGroup(pix_doodle);
    removeFromGroup(pix_shoot);
    delete pix_doodle;
    delete pix_shoot;
    delete playersound;
    scene()->removeItem(this);  // After HERE cannot access scene() !!
    game->scene->clear();
    qDebug() << "Delete All Items";
    game->gameover = new Gameover(-game->offsetY, "Doodler");
}

void Player::setImg(QString file, bool set)
{
    QPixmap pix(file);
    pix_doodle->setPixmap(pix.scaled(100,100, Qt::KeepAspectRatio));
    if(set) {
        setTransform(Lpos);
    }
    else {
        setTransform(isleft? Lpos:Rpos);
    }
    pix_shoot->setVisible(shootEnable && shoot_angle != 1000);
}

void Player::keyPressEvent(QKeyEvent *e)
{
    if(KeyEnable) {
        switch(e->key()) {
            case Qt::Key_Left: {
                if(!e->isAutoRepeat() && !LkeyLongPress) {
                    if(!RkeyLongPress){
                        tx = 0;
                        isleft = true;
                    }
                    LkeyLongPress = true;
//                    qDebug() << "L_Press";
                }
                break;
            }
            case Qt::Key_Right: {
                if(!e->isAutoRepeat() && !RkeyLongPress) {
                    if(!LkeyLongPress){
                        tx = 0;
                        isleft = false;
                    }
                    RkeyLongPress = true;
//                    qDebug() << "R_Press";
                }
                break;
            }
            case Qt::Key_Space: {
                if(shootEnable)
                    if(!e->isAutoRepeat()) {
                        scene()->addItem(new Bullet());
                        shoot_angle = 0;
                    }
                break;
            }

            default:    break;
        }
    }
    if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
        if(!ispause) {
            game->timer->stop();
            game->pause->setPos(0, game->offsetY);
            game->pause->show();
            ispause = true;
        }
        else {
            game->timer->start(20);
            game->pause->hide();
            ispause = false;
        }
    }
}

void Player::keyReleaseEvent(QKeyEvent *e)
{
    switch(e->key()) {
        case Qt::Key_Left: {
            if(!e->isAutoRepeat() && LkeyLongPress) {
                LkeyLongPress = false;
                if(!RkeyLongPress) {
                    tx = 0;
                }
                else {
                    isleft = false;
                    tx = 0;
                }
//                qDebug() << "L_Release";
            }
            break;
        }
        case Qt::Key_Right: {
            if(!e->isAutoRepeat() && RkeyLongPress) {
                RkeyLongPress = false;
                if(!LkeyLongPress) {
                    tx = 0;
                }
                else {
                    isleft = true;
                    tx = 0;
                }
//                qDebug() << "R_Release";
            }
            break;
        }
        default: {
            break;
        }
    }
}

void Player::bounce(double v0y)
{
    // Effects at Next first iteration
    ty = 0.0;
    Y_i = y();
    V0y = Vy = v0y;
}

void Player::GameOver()
{
    qDebug() << "GameOver";
    delete this;    // Delete All Items
}

void Player::setshootEnable(bool en)
{
    shootEnable = en;
}

void Player::setStatus(int s)
{
    status = s;
}

void Player::move()
{
    // moveX
    tx += game->timer->remainingTime();
    if(LkeyLongPress || RkeyLongPress) {
        if(isleft) {
            if(x() + boundingRect().width() > 0)
                setX(x() - (tx > Tx? max_Vx : max_Vx*tx/Tx));
            else
                setX(scene()->width());
        }
        else {
            if(x() < scene()->width())
                setX(x() + (tx > Tx? max_Vx : max_Vx*tx/Tx));
            else
                setX(-boundingRect().width());
        }
    }

    // moveY
    if(status == 0) {
        ty += game->timer->remainingTime()*0.001;
        Vy = V0y + g*ty;
        if(fabs(Vy) < 800.0)
            setY(Y_i+V0y*ty + 0.5*g*ty*ty);
        else // SLOW protect: ensure dy in range of Platform.height
            setY(y() + 15 * (Vy > 0? 1:-1));
        V0y = -max_Vy;
    }
    else if(status == 1) {  // accel status
        setY(y() - abs(Vy*0.05));
        ty = 0.0;
        Y_i = y();
    }

    // set image
    if(shoot_angle == 1000) // not shoot
        setImg(":/img/player_left0");
    else {
        t_shoot += game->timer->remainingTime();
        if(t_shoot < 500) {
            setImg(":/img/player_shoot0");
        }
        else {
            setImg(":/img/player_left0");
            shoot_angle = 1000;
            t_shoot = 0;
        }
    }

    // GameOver condition
    if(y() > game->offsetY + scene()->height()) {
        GameOver();
        return;
    }

    // set scene offset
    game->offsetScene();

    // Check colliding Items with Player
    QList<QGraphicsItem *> col_items = collidingItems();
    for(auto coll = col_items.begin(); coll < col_items.end(); ++coll) {
        // 1st check (Normal): <Accel, Hazard>
        if(status == 0) {
//            if(typeid(*(col_items[i])) == typeid(Prop)) {
            if(Prop *pp = dynamic_cast<Prop *>(*coll)) {
                setTransform(Lpos);
                setImg(":/img/player_left0", true);
                pp->touch();        // Polymorphism HERE!!
                if(dynamic_cast<Jetpack *>(*coll)) {  // IS Jetpack
                    qDebug() << "IS JETPACK";
                    V0y = Vy = -550.0;
                }
                else {
                    qDebug() << "NOT  JETPACK (PROP)";
                    V0y = Vy = -200.0;
                }
                continue;
            }
            else if(Hazard *hh = dynamic_cast<Hazard *>(*coll)) {
                if(Vy > 0.0) {  // Falling
                    // Ensure accurate collision part
                    if(y() + boundingRect().height() >= (*coll)->y() &&
                       y() + boundingRect().height() <= (*coll)->y() + 0.8*(*coll)->boundingRect().height() &&
                       x() + 0.75*boundingRect().width()  >= (*coll)->x() &&
                       x() + 0.25*boundingRect().width()  <= (*coll)->x() + (*coll)->boundingRect().width()
                      ){
                        if(Monster *m = dynamic_cast<Monster *>(*coll)) {
                            bounce(-max_Vy*2.0);
                            m->touch();
                            break;
                        }
                    }
                }
                else {
                    GameOver();
                    return;
                }
            }
            else if(Platform *p = dynamic_cast<Platform *>(*coll)) {
    //            if(typeid(*(col_items[i])) == typeid(Platform)) {
                if(Vy > 0.0) {  // Falling
                    // Ensure accurate collision part
                    if(y() + boundingRect().height() >= (*coll)->y() &&
                       y() + boundingRect().height() <= (*coll)->y() + 0.8*(*coll)->boundingRect().height() &&
                       x() + 0.75*boundingRect().width()  >= (*coll)->x() &&
                       x() + 0.25*boundingRect().width()  <= (*coll)->x() + (*coll)->boundingRect().width())
                    {
                        p->touch();
                        if(typeid(*(*coll)) == typeid(Platform)) {
                            bounce();
                            break;
                        }
                    }
                }
            }
        }
        else if(status == 1) { //accel status
            if(Monster *m = dynamic_cast<Monster *>(*coll)) {
                delete m;
                break;
            }
        }
    }
    game->clearScene();
}

