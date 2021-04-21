#ifndef BOT_h
#define BOT_H

enum Boat {PIRATE, WAR, GUNPOWDER};

struct vector{
    float x;
    float y;
};

struct bot{
    GdkRectangle rect;
    float dir;
    float speed;
    guint event;
    enum Boat type;
};

void bot_move(struct Stack path);

#endif