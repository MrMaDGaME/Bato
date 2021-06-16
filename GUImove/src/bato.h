#include "bot.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "struct.h"

#ifndef BATO_H
#define BATO_H

/*
//#define BOAT_RECTS 13
typedef struct Ball{
    GdkRectangle rect;
    float dir;
    float speed;
    float dis;
    guint event;
} Ball;

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
    GdkRectangle rect;
    float dir;
    float speed;
    guint event;
    enum Boat type;
    int hp;
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
} UserInterface;

typedef struct Game{
    struct bot bot_list[6];
    Player p;
    UserInterface ui;
    Isle island;
} Game;
*/

float degToRad(float deg)
{
  return deg/57.2957795147;
}

float radToDeg(float rad)
{
  return rad*57.2957795147;
}

double modulo(double x, double y);
void draw_arena(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void redraw_item(GtkDrawingArea *area, GdkRectangle *old, GdkRectangle *new);
gboolean player_move(gpointer user_data);
gboolean speed_to_sail(gpointer user_data);
gboolean progress_bar(gpointer user_data);
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data);

#endif
