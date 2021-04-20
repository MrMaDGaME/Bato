#ifndef GRAPH_H
#define GRAPH_H

enum Boat = {PIRATE, WAR, GUNPOWDER};

struct bot{
    GdkRectangle rect;
    float dir;
    float speed;
    guint event;
    enum Boat type;
};

void move(struct Stack path);

#endif