#ifndef STRUCT_H
#define STRUCT_H

#include <gtk/gtk.h>

enum Boat {PIRATE, WAR, GUNPOWDER};

typedef struct vector{
    float x;
    float y;
} vector;

typedef struct Ball{
    GdkRectangle rect;
    float dir;
    float speed;
    float dis;
    guint event;
} Ball;

typedef struct Planche{
    GdkRectangle rect;
    int used;
    guint event;
} Planche;

typedef struct Player{
    GdkRectangle rect;
    float dir;
    int hp;
    float speed;
    float sail;
    struct Ball ball;
    guint event;
} Player;

typedef struct bot{
    struct Stack *path;
  int alive;
  vector spawn_point;
  GdkRectangle rect;
  float dir;
  float speed;
  guint event;
  enum Boat type;
  int hp;
  struct Ball ball;
} bot;

typedef struct Isle{
    GdkRectangle rect[819];
} Isle;

typedef struct UserInterface
{
    GtkWindow* window;
    GtkDrawingArea* area;
    GtkProgressBar *lifebar;
    GtkProgressBar *sailbar;
    GtkLabel *roundLabel;
} UserInterface;

typedef struct Game{
  struct graph *graph;
  int round;
  int nb_bots;
  int bots_left;
  struct bot bot_list[6];
  Planche planche1;
  Planche planche2;
  Player p;
  UserInterface ui;
  Isle island;
} Game;

#endif
