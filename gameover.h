#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QPixmap>
#include <QKeyEvent>

class Gameover: public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    Gameover(int s, QString n);
    ~Gameover();
    void keyPressEvent(QKeyEvent *e) override;
    void setImg();

private:
    QGraphicsPixmapItem *title;
    QGraphicsTextItem   *score;
    QGraphicsTextItem   *hscore;
    QGraphicsTextItem   *name;
    QGraphicsTextItem   *hint1;
    QGraphicsTextItem   *hint2;
};

#endif // GAMEOVER_H
