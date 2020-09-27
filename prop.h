#ifndef PROB_H
#define PROB_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <platform.h>

class Prop: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Prop(Platform *p);
    ~Prop();
    virtual void setImg(int i);
    virtual void touch();

public slots:
    virtual void anime();

private:
    // For touch() Animation
    static const int pic[][4];
    int state;
    bool istouched;

};

#endif // PROB_H
