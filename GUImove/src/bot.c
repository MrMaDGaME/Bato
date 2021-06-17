#include "bot.h"

#define ROT_STEP 0.025
#define BOAT_WIDTH 44
#define BOAT_HEIGHT 20
#define HEIGHT 760
#define WIDTH 1140
#define PI 3.14159265359

double modula(double x, double y)
{
    /*x modulo y*/
    x-=y*abs(x/y);
    if (x>=0.) return (x);
    else return (x+y);
}       


void redro_item(GtkDrawingArea *area, GdkRectangle *old, GdkRectangle *new)
{
  gdk_rectangle_union(old, new, old);

  gtk_widget_queue_draw_area(GTK_WIDGET(area),
			     (*old).x-((*old).width*2), (*old).y-((*old).width*2), (*old).width*4,(*old).width*4);
}

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
  game->bot_list[bot_index].rect.x = x;
  game->bot_list[bot_index].rect.y = y;
  redro_item(game->ui.area, &old, &game->bot_list[bot_index].rect);
}

void bot_kill(struct Game *game, int bot_index){
  GdkRectangle old = game->bot_list[bot_index].rect;
  game->bot_list[bot_index].rect.x = game->bot_list[bot_index].spawn_point.x;
  game->bot_list[bot_index].rect.y = game->bot_list[bot_index].spawn_point.y;
  redro_item(game->ui.area, &old, &game->bot_list[bot_index].rect);
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


void bot_move(struct Game *game, int bot_index){
  if(!game->bot_list[bot_index].path){
    printf("path null at index = %d\n", bot_index);
    err(1, "bot_move : path NULL\n");
  }
    struct chkpoint *target = peek(game->bot_list[bot_index].path);
    struct vector target_dir;
    //vecteur qui va du bot au joueur
    struct vector player_dir;
    //vecteur direction du bot;
    int bot_x = game->bot_list[bot_index].rect.x + 22;
    int bot_y = game->bot_list[bot_index].rect.y + 10;
    target_dir.x = target->x - bot_x;
    target_dir.y = target->y - bot_y;
    player_dir.x = cosf(game->bot_list[bot_index].dir);
    player_dir.y = - sinf(game->bot_list[bot_index].dir);

    if(target_dir.x < 10 && target_dir.y < 10){
        game->bot_list[bot_index].speed = 0;
	      pop(game->bot_list[bot_index].path);
        return;
    }
    printf("target_dir : x = %f, y = %f\n", target_dir.x, target_dir.y);
    printf("player_dir : x = %f, y = %f\n", player_dir.x, player_dir.y);
    printf("target : x = %d, y = %d\n", target->x, target->y);
    
    int angle_dir; //give the direction of the angle: 0 is right, 1 is left
    float angle_value; //the value of the angle in radian
    
    float preangle = (player_dir.x * target_dir.x - player_dir.y * target_dir.y) /
      (sqrtf(player_dir.x * player_dir.x + player_dir.y * player_dir.y) *
       sqrtf(target_dir.x * target_dir.x + target_dir.y * target_dir.y));
    
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
    printf("angle_value = %f\n", angle_value);
    if(angle_value >= 0.01){
        if(angle_value <= ROT_STEP){
            if(angle_dir){
                game->bot_list[bot_index].dir -= angle_value;
            }
            else{
                game->bot_list[bot_index].dir += angle_value;
            }
	    game->bot_list[bot_index].speed = 5;
        }
        else{
            if(angle_dir){
                game->bot_list[bot_index].dir -= ROT_STEP;
            }
            else{
                game->bot_list[bot_index].dir += ROT_STEP;
            }
	}
    }
    else{
      game->bot_list[bot_index].speed = 5;
    }
    printf("bot %d : speed = %f, dir = %f\nx = %d, y = %d\n", bot_index, game->bot_list[bot_index].speed, game->bot_list[bot_index].dir, game->bot_list[bot_index].rect.x, game->bot_list[bot_index].rect.y);

    /*GdkRectangle old = game->bot_list[bot_index].rect;
            
    game->bot_list[bot_index].rect.y = game->bot_list[bot_index].rect.y + (game->bot_list[bot_index].speed * sinf(game->bot_list[bot_index].dir));
    game->bot_list[bot_index].rect.x = game->bot_list[bot_index].rect.x + (game->bot_list[bot_index].speed * cosf(game->bot_list[bot_index].dir));

    game->bot_list[bot_index].dir = modula(game->bot_list[bot_index].dir, 2*PI);

    redro_item(game->ui.area, &old, &game->bot_list[bot_index].rect);
    return;*/
}


/*void bot_shoot(struct bot bot_list, int bot_index; gpointer user_data){
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
      angle_value1 = acos(preangle1);
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
      angle_value2 = acos(preangle2);
    }
  else
    {
      angle_dir2 = 1;
      angle_value2 = acos(-(preangle2));
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
*/
