#include <math.h>
#include <gtk/gtk.h>
#include "../../pathfinding/stack.h"
#include "../../pathfinding/graph.h"
#include "../../pathfinding/astar.h"

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

void bot_spawn(gpointer user_data, cairo_t *cr, int bot_index, enum Boat type);

int bot_move(struct bot *boat, struct Stack *path);

#endif
