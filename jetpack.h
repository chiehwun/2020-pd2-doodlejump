#ifndef JETPACK_H
#define JETPACK_H

#include <QObject>
#include "prop.h"

class Jetpack: public Prop
{
    Q_OBJECT
public:
    Jetpack(Platform *p);
    ~Jetpack();
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

#endif // JETPACK_H
