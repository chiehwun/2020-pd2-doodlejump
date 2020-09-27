#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QString>
#include <QPointF>
#include "bullet.h"
#include <QList>
#include <QtMath>

class Player: public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    Player();
    ~Player();
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    void bounce(double v0y = -max_Vy);
    void GameOver();
    void setshootEnable(bool en);
    void setStatus(int s);
    double Y_i;
    bool ispause;

public slots:
    void setImg(QString file, bool set = false);
    void move();
//    void scene_move();

private:
    // For move()
    bool LkeyLongPress;
    bool RkeyLongPress;
    bool isleft;
    const int Tx;
    const int max_Vx;
    int tx;
    QTransform Lpos;
    QTransform Rpos;

    // For jump()
    const static double max_Vy; // for default parameters bounce(...)
    const double g;
    double       Vy;
    double       V0y;
    double       ty;
    int          page;

    // Player state
    QGraphicsPixmapItem *pix_doodle;
    QGraphicsPixmapItem *pix_shoot;
    int shoot_angle;
    int t_shoot;
    bool KeyEnable;
    bool shootEnable;
    int status; // -1: GameOver
                //  0: normal
                //  1: accel


    // Media
    QMediaPlayer *playersound;

};

#endif // PLAYER_H
