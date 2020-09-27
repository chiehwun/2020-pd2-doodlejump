#include "game.h"
#include "platform_wood.h"
#include "prop.h"
#include "jetpack.h"
#include "monster.h"
#include "monster_blue.h"
#include<QDebug>

Game::Game(QGraphicsView *v):
    offsetY(0),
    page(0),
    record(QVector <int>()),
    view(v),
    timer(new QTimer()) // create Timer first (player, Items...)
{
    // random init
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    // scene settings
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,view->width(),view->height());
    scene->setBackgroundBrush(QBrush(QImage(":/img/bg")));

    // graphicsView settings
    view->setScene(scene);
    view->setHorizontalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy    (Qt::ScrollBarAlwaysOff);
    view->setFixedSize(600,800);
//    view->setFocusPolicy(Qt::NoFocus);


}

Game::~Game()
{
    delete player;
    delete view;
    scene->clear();
    delete scene;
}


void Game::reset()
{
    // create topBar
    topBar = new QGraphicsPixmapItem();
    QPixmap pix(":/img/top");
    pix = pix.copy(QRect(0,0,319,45));
    topBar->setPixmap(pix.scaled(600,30, Qt::IgnoreAspectRatio));
    topBar->setZValue(std::numeric_limits<qreal>::max());
    scene->addItem(topBar);
    topBar->setPos(0,0);

    // create score
    score = new QGraphicsTextItem();
    QFont font;
    font.setFamily("Courier");
    font.setPixelSize(15);
    font.setStyle(QFont::StyleItalic);
    score->setFont(font);
    score->setPos(0,0);
    score->setPlainText("0");
    score->setZValue(std::numeric_limits<qreal>::max());
    scene->addItem(score);

    // create pause
    pause = new QGraphicsPixmapItem();
    pix.load(":/img/pause");
    pause->setPixmap(pix.scaled(600,800, Qt::IgnoreAspectRatio));
    scene->addItem(pause);
    pause->hide();

    // create player
    player = new Player();
    scene->addItem(player);
    player->setPos(100, player->Y_i);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    offsetY = 0;

    spawn(0);
    spawn(1);

    // REMIND to COMMENT
//    Test();
}

void Game::Test()
{
    // **Test create Hazard
//    scene->addItem(new Hazard(0,75));
//    scene->addItem(new Hazard(100,100));
        // **Test create Monsters
//    scene->addItem(new Monster(300, -300));
//    scene->addItem(new Monster_blue(200, 100));

//    // **Test create Prop
//    Platform *p = new Platform(310, 300);
//    scene->addItem(p);
//    scene->addItem(new Jetpack(p));
//    // **Test create Platform_Wood
//    scene->addItem(new Platform_Wood(100,200));
//    scene->addItem(new Platform_Wood(200,50));
//    scene->addItem(new Platform_Wood(300,125));
//    scene->addItem(new Platform_Wood(400,30));
}

void Game::clearScene()
{
    // Delete items which are out of scene
    QList<QGraphicsItem *> L = scene->items(QRect(-500, scene->height() + offsetY,
                                              scene->width() + 500, scene->height()),
                                              Qt::ContainsItemShape);
    if(!L.empty()) {
        for(int i = 0, n = L.size(); i < n; i++) {
//            if(typeid(*(L.at(i))) != typeid(*this)) {     // trying...
//            if(!dynamic_cast<Player *>(L[i])) {
            if(dynamic_cast<Platform *>(L[i]) ||
               dynamic_cast<Hazard *>(L[i])   /*||
               (dynamic_cast<Prop *>(L[i]) && )*/) {    // type == Platform
                delete L.at(i);
            }
        }
    }
}

void Game::offsetScene()
{
    // set scene offset
    if(player->y() < offsetY + 200) {
        offsetY = player->y() - 200;
        int pageN = (-offsetY) % (int)scene->height();
        if(pageN < page) {
            spawn();
        }
        scene->setSceneRect(0, offsetY, scene->width(), scene->height());
        page = pageN;
    }

    // update topBar, score position
    topBar->setY(offsetY);
    score->setY(offsetY);
    score->setPlainText(QString::number(-offsetY));
}

void Game::spawn(int page)
{
    for(auto i = record.begin(); i < record.end(); ++i) {
        if(*i >= -(offsetY + 800*(1-page)) && *i < -(offsetY - 800*page)) {
            QGraphicsTextItem *history = new QGraphicsTextItem();
            QFont font;
            font.setFamily("Courier");
            font.setPixelSize(15);
            font.setStyle(QFont::StyleItalic);
            font.setUnderline(true);
            history->setFont(font);
            history->setPos(0,scene->height() - *i);
            history->setPlainText(QString::number(*i));
            history->setZValue(std::numeric_limits<qreal>::max());
            scene->addItem(history);
        }
    }
    for(int y = offsetY + 800*(1-page); y >= offsetY - 800*page; y -= 60) {
        if(randInt(0,10)) { // Platform
            Platform *p = new Platform(randInt(0,500), y+randInt(-10,10));
            scene->addItem(p);
            // Accel items
            if(!randInt(0,20)) {
                if(randInt(0,3)) {
                    scene->addItem(new Prop(p));
                }
                else {
                    scene->addItem(new Jetpack(p));
                }
            }
        }
        else if(randInt(0, 5)){ // Platform_Wood
            scene->addItem(new Platform_Wood(randInt(0,500), y+randInt(-10,10)));
        }
        else {  // Hazard
            y -= 100;
            if(randInt(0,5)) {
                if(randInt(0,1)) {
                    scene->addItem(new Monster(randInt(0,500), y));
                }
                else {
                    scene->addItem(new Monster_blue(randInt(0,500), y));
                }
            }
            else {
                scene->addItem(new Hazard(randInt(0,500), y+randInt(-10,10)));
            }
        }


//        qDebug() << "Create P@:" << y;
    }
}

int Game::randInt(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}
