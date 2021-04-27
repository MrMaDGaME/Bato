#ifndef BATO_H
#define BATO_H

typedef struct Round
{
    int nb_round;
    int ennemies_left;
    int ennemies_in_round;
} Round;

typedef struct Player{
    GdkRectangle rect;
    float dir;
    float speed;
    float sail;
    guint event;
} Player;

typedef struct UserInterface
{
    GtkWindow* window;
    GtkDrawingArea* area;
} UserInterface;

typedef struct Game{
    Round round;
    Player p;
    UserInterface ui;
} Game;

float degToRad(float deg)
{
  return deg/57.2957795147;
}

float radToDeg(float rad)
{
  return rad*57.2957795147;
}

void draw_arena(cairo_t *cr);
gboolean on_draw(cairo_t *cr, gpointer user_data);
void redraw_item(GtkDrawingArea *area, GdkRectangle *old, GdkRectangle *new);
gboolean player_move(gpointer user_data);
gboolean speed_to_sail(gpointer user_data);
gboolean on_key_press(GdkEventKey *event, gpointer user_data);

#endif