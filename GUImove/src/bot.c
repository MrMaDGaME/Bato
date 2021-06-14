#include "bot.h"

#define ROT_STEP 0.025
#define BOAT_WIDTH 44
#define BOAT_HEIGHT 20
#define HEIGHT 760
#define WIDTH 1140
#define PI 3.14159265359


void bot_spawn(gpointer user_data, cairo_t *cr, int bot_index, enum Boat type){
  struct Game *game = user_data;
  struct bot new_bot;
  int x;
  int y;
  switch(bot_index){
  case 0: x = 50; y = 50; break;
  case 1: x = WIDTH/2; y = 50; break;
  case 2: x = WIDTH - 50 - BOAT_WIDTH; y = 50 ; break;
  case 3: x = 50; y = HEIGHT - 50 - BOAT_HEIGHT; break;
  case 4: x = WIDTH/2; y = HEIGHT - 50 - BOAT_HEIGHT; break;
  case 5: x = WIDTH - 50 - BOAT_WIDTH; y = HEIGHT - 50 - BOAT_HEIGHT; break;
  };
  new_bot.rect = {x, y, x + BOAT_WIDTH, y + BOAT_HEIGHT};
  if(bot_index < 3){
    new_bot.dir = PI/2;
  }
  else{
    new_bot.dir = -PI/2;
  }
  new_bot.speed = 0;
  new_bot.type = type;
  switch(type){
  case GUNPOWDER: new_bot.hp = 10; break;
  case WAR: new_bot.hp = 50; break;
  case PIRATE: new_bot.hp = 20; break;
  }
  new_bot.event = 0;
  game->bot_list[bot_index] = new_bot;

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
