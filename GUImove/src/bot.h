#ifndef BOT_H
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
    int hp;
};

int bot_move(struct bot *boat, struct Stack *path);

#endif