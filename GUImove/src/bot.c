#include <math.h>
#include <gtk/gtk.h>
#include "../../pathfinding/stack.h"
#include "../../pathfinding/graph.h"
#include "../../pathfinding/astar.h"
#include "bot.h"

#define ROT_STEP 0.025

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
