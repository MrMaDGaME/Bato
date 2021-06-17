#include "bot.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "struct.h"

#ifndef BATO_H
#define BATO_H


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
gboolean path_compute(gpointer user_data);
//calcule l'itineraire et elle le met dans la stack et free precedente
//pour chaque bot
gboolean move_bots(gpointer user_data);
//fonction chapeau de bot_move
gboolean speed_to_sail(gpointer user_data);
gboolean progress_bar(gpointer user_data);
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data);
gboolean dist_ball (gpointer user_data);
gboolean tile_collision(Game *game, int tile_x, int tile_y);
gboolean map_collision(gpointer user_data);
gboolean ball_move(gpointer user_data);
gboolean ball_b_move(gpointer user_data);

#endif
