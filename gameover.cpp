#include "gameover.h"
#include <QObject>
#include <QDebug>
#include "game.h"

extern Game *game;
Gameover::Gameover(int s, QString n):
    title       (new QGraphicsPixmapItem()),
    score       (new QGraphicsTextItem()),
    hscore      (new QGraphicsTextItem()),
    name        (new QGraphicsTextItem()),
    hint1       (new QGraphicsTextItem()),
    hint2       (new QGraphicsTextItem())
{
    // record
    game->record.append(s);
    int max = *std::max_element(game->record.begin(), game->record.end());
    qDebug() << "max: " << max;
    // set Title
    setImg();

    QFont font;
    font.setFamily("Courier");
    font.setPixelSize(40);
    font.setStyle(QFont::StyleItalic);

    score->setFont(font);
    score->setPlainText(QString::number(s));
    addToGroup(score);
    score->setPos(0.57*game->scene->width(),
                  0.33*game->scene->height());

    hscore->setFont(font);
    hscore->setPlainText(QString::number(max));
    addToGroup(hscore);
    hscore->setPos( 0.57*game->scene->width(),
                   0.415*game->scene->height());

    name->setFont(font);
    name->setPlainText(n);
    name->setPos(0.57*game->scene->width(),
                  0.5*game->scene->height());
    addToGroup(name);

    font.setPixelSize(20);
    hint1->setFont(font);
    hint1->setPlainText("< Press Enter >");
    hint1->setPos(0.59*game->scene->width(),
                   0.65*game->scene->height());
    addToGroup(hint1);

    hint2->setFont(font);
    hint2->setPlainText("< Press Backspace >");
    hint2->setPos( 0.05*game->scene->width(),
                   0.58*game->scene->height());
    addToGroup(hint2);

    game->scene->addItem(this);
    game->scene->setSceneRect(QRect(0,0,600,800));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

Gameover::~Gameover()
{
    removeFromGroup(title);
    removeFromGroup(score);
    removeFromGroup(hscore);
    removeFromGroup(name);
    removeFromGroup(hint1);
    removeFromGroup(hint2);
    delete title;
    delete score;
    delete hscore;
    delete name;
    delete hint1;
    delete hint2;
    game->scene->removeItem(this);
    game->scene->clear();
    game->reset();
    qDebug() << "~Gameover()";
}

void Gameover::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
        qDebug() << "reset";
        delete this;
        return;
    }
}

void Gameover::setImg()
{
    QPixmap pix(":/img/endtitle");
    title->setPixmap(pix);
    addToGroup(title);
    title->setPos(0,0);
}
