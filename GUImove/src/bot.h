#include <math.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <err.h>
#include "../../pathfinding/stack.h"
#include "../../pathfinding/graph.h"
#include "../../pathfinding/astar.h"
#include "struct.h"

#ifndef BOT_H
#define BOT_H

void new_round(struct Game *game);
//incrémente les veriables de round et nb_bots

void choose_bot(struct Game *game);
//choisi un bot en fonction de la manche et appelle spawn_bot

void spawn_bot(struct Game *game, int bot_index);
//tp le bot dans l'arène, alive = 1, decremente bots_left, reinitialise hp

void bot_kill(struct Game *game, int bot_index);
//tp le bot hors map, alive = 0, réinitialise speed, dir
//check si new round

//void bot_spawn(gpointer user_data, cairo_t *cr, int bot_index, enum Boat type);

int bot_move(struct bot *boat, struct Stack *path);

#endif
