#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "platform.h"
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QBrush>
#include <QScrollBar>
#include "platform.h"
#include <QTime>
#include "hazard.h"
#include <QTimer>
#include <QGraphicsItemGroup>
#include <gameover.h>

class Game
{
public:
    Game(QGraphicsView *v);
    ~Game();
    void reset();   // create player, spawn items
    void Test();
    void clearScene();
    void offsetScene();
    void spawn(int page = 1);       // by one Page
    int offsetY;
    int page;
    int randInt(int low, int high);
    QVector<int> record;
    QGraphicsScene      *scene;
    QGraphicsView       *view;
    QGraphicsPixmapItem *topBar;
    QGraphicsTextItem   *score;
    QGraphicsPixmapItem *pause;
    Gameover            *gameover;
    Player              *player;
    QTimer              *timer;

};

#endif // GAME_H
