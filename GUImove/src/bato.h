#ifndef BATO_H
#define BATO_H

//#define BOAT_RECTS 13

typedef struct Player{
    GdkRectangle rect;
    float dir;
    int hp;
    float speed;
    float sail;
    guint event;
} Player;

typedef struct UserInterface
{
    GtkWindow* window;
    GtkDrawingArea* area;
    GtkProgressBar *lifebar;
    GtkProgressBar *sailbar;
} UserInterface;

typedef struct Game{
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

void draw_arena(GtkWidget *widget, cairo_t *cr, gpointer user_data);
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void redraw_item(GtkDrawingArea *area, GdkRectangle *old, GdkRectangle *new);
gboolean player_move(gpointer user_data);
gboolean speed_to_sail(gpointer user_data);
gboolean progress_bar(gpointer user_data);
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data);

#endif
