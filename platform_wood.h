#ifndef PLATFORM_WOOD_H
#define PLATFORM_WOOD_H
#include "platform.h"
#include <QObject>

class Platform_Wood: public Platform
{
    Q_OBJECT
public:
    Platform_Wood(int x, int y);
    void setImg() override;
    void touch() override;
    bool istouched;


public slots:
    void anime();

private:
    // For touch() Animation
    static const int pic[4][4];
    int state;
    double Y_i;
    double g;
    double max_Vy;
    double Vy;
    double ty;
};

#endif // PLATFORM_WOOD_H
