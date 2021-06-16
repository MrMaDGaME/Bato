#include "bot.h"

#define ROT_STEP 0.025
#define BOAT_WIDTH 44
#define BOAT_HEIGHT 20
#define HEIGHT 760
#define WIDTH 1140
#define PI 3.14159265359


void new_round(struct Game *game){
  game->round += 1;
  game->nb_bots += 2;
  game->bots_left = game->nb_bots;
}

void choose_bot(struct Game *game){
  if(game->round < 3){
    for(int i = 0; i<3; i++){
      if(!game->bot_list[i].alive){
	spawn_bot(game, i);
	return;
      }
    }
    err(1, "pas de bot dispo (manche <= 2)");
  }
  else{
    srand(time(NULL));
    int i = rand() % 6;
    int k = 0;
    while(game->bot_list[i].alive){
      k++;
      i = rand() % 6;
      if(k > 6){
	err(1, "pas de bot dispo (manche > 2)");
      }
    }
    spawn_bot(game, i);
  }
}

void spawn_bot(struct Game *game, int bot_index){
  int x;
  int y;
  int hp;
  switch(bot_index){
  case 0: x = 50; y = 50; hp = 20; break;
  case 1: x = WIDTH/2; y = 50; hp = 20; break;
  case 2: x = WIDTH - 50 - BOAT_WIDTH; y = 50; hp = 20; break;
  case 3: x = 50; y = HEIGHT - 50 - BOAT_HEIGHT; hp = 10; break;
  case 4: x = WIDTH/2; y = HEIGHT - 50 - BOAT_HEIGHT; hp = 10; break;
  case 5: x = WIDTH - 50 - BOAT_WIDTH; y = HEIGHT - 50 - BOAT_HEIGHT; hp = 50; break;
  default: err(1, "invalid index in spawn_bot");
  };
  game->bot_list[bot_index].hp = hp;
  game->bots_left -= 1;
  game->bot_list[bot_index].alive = 1;
  GdkRectangle old = game->bot_list[bot_index].rect;
  game->bot_list[bot_index].rect = {x, y, BOAT_WIDTH, BOAT_HEIGHT};
  redraw_item(game->ui.area, &old, &game->bot_list[bot_index].rect);
}

void bot_kill(struct Game *game, int bot_index){
  GdkRectangle old = game->bot_list[bot_index].rect;
  game->bot_list[bot_index].rect = {game->bot_list[bot_index].spawn_point.x, game->bot_list[bot_index].spawn_point.y, BOAT_WIDTH, BOAT_HEIGHT};
  redraw_item(game->ui.area, &old, &game->bot_list[bot_index].rect);
  game->bot_list[bot_index].alive = 0;
  game->bot_list[bot_index].dir = 0;
  game->bot_list[bot_index].speed = 0;
  if(game->bots_left > 0){
    choose_bot(game);
    return;
  }
  int nb_alive = 0;
  for(int i = 0; i<6; i++){
    if(game->bot_list[bot_index].alive){
      nb_alive++;
    }
  }
  if(nb_alive == 0){
    new_round(game);
  }
}

/*void bot_spawn(gpointer user_data, cairo_t *cr, int bot_index, enum Boat type){
    Game *game = user_data;
    struct bot *new_bot = malloc(sizeof(struct bot));
    int x = 0;
    int y = 0;

    switch(bot_index){
        case 0: x = 50; y = 50; break;
        case 1: x = WIDTH/2; y = 50; break;
        case 2: x = WIDTH - 50 - BOAT_WIDTH; y = 50 ; break;
        case 3: x = 50; y = HEIGHT - 50 - BOAT_HEIGHT; break;
        case 4: x = WIDTH/2; y = HEIGHT - 50 - BOAT_HEIGHT; break;
        case 5: x = WIDTH - 50 - BOAT_WIDTH; y = HEIGHT - 50 - BOAT_HEIGHT; break;
    };

    GdkRectangle rct = {x, y, x + BOAT_WIDTH, y + BOAT_HEIGHT};
    new_bot->rect = rct;


    if(bot_index < 3){
        new_bot->dir = PI/2;
    }
    else{
        new_bot->dir = -PI/2;
    }

    new_bot->speed = 0;
    new_bot->type = type;

    switch(type){
        case GUNPOWDER: new_bot->hp = 10; break;
        case WAR: new_bot->hp = 50; break;
        case PIRATE: new_bot->hp = 20; break;
    }

    new_bot->event = 0;
    struct Ball ball =
      {
	.rect = {1, 1, 5, 5},
	.dir = 0,
	.speed = 0,
	.dis = 0, //1000 arrêt
	.event = 0,
      };
    new_bot->ball = ball;
    
    game->bot_list[bot_index] = *new_bot;

    int dir = 0;

    cairo_set_source_rgb(cr, 1, 0, 1);

    cairo_move_to (cr, x+BOAT_WIDTH/2, y+BOAT_HEIGHT/2);
    cairo_rel_line_to(cr, sinf(dir)*BOAT_HEIGHT/2, -cosf(dir)*BOAT_HEIGHT/2);
    cairo_rel_line_to(cr, -cosf(dir)*BOAT_WIDTH/2, -sinf(dir)*BOAT_WIDTH/2);
    cairo_rel_line_to(cr, -sinf(dir)*BOAT_HEIGHT, cosf(dir)*BOAT_HEIGHT);
    cairo_rel_line_to(cr, cosf(dir)*BOAT_WIDTH/2, sinf(dir)*BOAT_WIDTH/2);
    cairo_close_path (cr);
    cairo_fill(cr);

    cairo_move_to (cr, x+BOAT_WIDTH/2, y+BOAT_HEIGHT/2);
    cairo_rel_line_to(cr, sinf(dir)*BOAT_HEIGHT/2, -cosf(dir)*BOAT_HEIGHT/2);
    cairo_rel_line_to(cr, cosf(dir)*BOAT_WIDTH/2, sinf(dir)*BOAT_WIDTH/2);
    cairo_rel_line_to(cr, -sinf(dir)*BOAT_HEIGHT, cosf(dir)*BOAT_HEIGHT);
    cairo_rel_line_to(cr, -cosf(dir)*BOAT_WIDTH/2, -sinf(dir)*BOAT_WIDTH/2);
    cairo_close_path (cr);
    cairo_fill(cr);
}
*/
int bot_move(struct bot *boat, struct Stack *path){
    //return 1 if target is reached, else 0
    struct chkpoint *target = pop(path);
    struct vector target_dir;
    struct vector player_dir;
    target_dir.x = target->x - boat->rect.x;
    target_dir.y = target->y - boat->rect.y;
    player_dir.x = cosf(boat->dir);
    player_dir.y = - sinf(boat->dir);

    if(!target_dir.x && !target_dir.y){
        boat->speed = 0;
        return 1;
    }
    
    int angle_dir; //give the direction of the angle: 0 is right, 1 is left
    float angle_value; //the value of the angle in radian
    
    float preangle = (player_dir.x * target_dir.x - player_dir.y * target_dir.y) /
        sqrtf(player_dir.x * player_dir.x + player_dir.y * player_dir.y) *
        sqrtf(target_dir.x * target_dir.x + target_dir.y * target_dir.y);
    
    if(preangle > 0.0)
    {
        angle_dir = 0;
        angle_value = acos(preangle);
    }
    else
    {
        angle_dir = 1;
        angle_value = acos(-(preangle));
    }
    if(angle_value != 0){
        if(angle_value <= ROT_STEP){
            if(angle_dir){
                boat->dir -= angle_value;
            }
            else{
                boat->dir += angle_value;
            }
        }
        else{
            if(angle_dir){
                boat->dir -= ROT_STEP;
            }
            else{
                boat->dir += ROT_STEP;
            }
        }
    }
    else{
        boat->speed = 5;
    }
    return 0;
}


void bot_shoot(struct bot bot_list, int bot_index; gpointer user_data){
  struct Game *game = user_data;
  struct Player player = game->p;
  struct bot *boat = malloc(sizeof(struct bot));
  *boat = bot_list[bot_index];
  struct vector target;
  struct vector target_dir;
  struct vector player_dir1;
  struct vector player_dir2;
  target.x = player.rect.x;
  target.y = player.rect.y;
  target_dir.x = target.x - boat->rect.x;
  target_dir.y = target.y - boat->rect.y;
  player_dir1.x = cosf(boat->dir + PI/2);
  player_dir1.y = - sinf(boat->dir + PI/2);
  player_dir2.x = cosf(boat->dir - PI/2);
  player_dir2.y = - sinf(boat->dir - PI/2);

  //Angle à droite
  int angle_dir1; //give the direction of the angle: 0 is right, 1 is left
  float angle_value1; //the value of the angle in radian
  float preangle1 = (player_dir1.x * target_dir.x - player_dir1.y * target_dir.y) /
    sqrtf(player_dir1.x * player_dir1.x + player_dir1.y * player_dir1.y) *
    sqrtf(target_dir.x * target_dir.x + target_dir.y * target_dir.y);
  if(preangle1 > 0.0)
    {
      angle_dir1 = 0;
      angle_value1 = acos(preangl1);
    }
  else
    {
      angle_dir1 = 1;
      angle_value1 = acos(-(preangle1));
    }

  //Angle à gauche
  int angle_dir2; //give the direction of the angle: 0 is right, 1 is left
  float angle_value2; //the value of the angle in radian
    
  float preangle2 = (player_dir2.x * target_dir.x - player_dir2.y * target_dir.y) /
    sqrtf(player_dir2.x * player_dir2.x + player_dir2.y * player_dir2.y) *
    sqrtf(target_dir.x * target_dir.x + target_dir.y * target_dir.y);
    
  if(preangle2 > 0.0)
    {
      angle_dir2 = 0;
      angle_value2 = acos(preangl2);
    }
  else
    {
      angle_dir2 = 1;
      angle_value2 = acos(-(preangl2));
    }

  //choix de l'angle
  int angle_dir;
  float angle_value;
  if(angle_value1 > angle_value2){
    angle_dir = angle_dir2;
    angle_value = angle_value2;
  }
  else{
    angle_dir = angle_dir1;
    angle_value = angle_value1;
  }
  
  if(angle_value != 0){
    if(angle_value <= ROT_STEP){
      if(angle_dir){
	boat->dir -= angle_value;
      }
      else{
	boat->dir += angle_value;
      }
    }
    else{
      if(angle_dir){
	boat->dir -= ROT_STEP;
      }
      else{
	boat->dir += ROT_STEP;
      }
    }
  }
  else{
    GdkRectangle old = game->boat.ball.rect;
    game->boat.ball.rect.x = game->boat.rect.x + 21;// * cosf(game->p.dir);
    game->boat.ball.rect.y = game->boat.rect.y - 10;// * sinf(game->p.dir);
    //à inverser si ça tire dans le mauvais sens j'ai mis les directions au pif
    if(angle_value1 > angle_value2){
      game->boat.ball.dir = game->boat.dir - 190;
    }
    else{
      game->boat.ball.dir = game->boat.dir + 190;
    }
    game->boat.ball.speed = 6;
    redraw_item(game->ui.area, &old, &game->p.ball.rect);
  }
  free(boat);
}
