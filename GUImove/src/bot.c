#include <math.h>
#include "bot.h"
#include "../../pathfinding/stack.h"
#include "../../pathfinding/astar.h"

void bot_move(struct bot boat, struct Stack path){
    struct chkpoint *target = pop(path);
    struct vector target_dir;
    struct vector player_dir;
    target_dir.x = target->x - boat.rect.x;
    target_dir.y = target->y - boat.rect.y;
    player_dir.x = cosf(boat.dir);
    player_dir.y = - sinf(boat.dir);
    
    int angle_dir; //give the direction of the angle: 0 is right, 1 is left
    float angle_value; //the value of the angle in radian
    
    float preangle = (player_dir.x * target_dir.x - player_dir.y * target_dir.y) /
        sqrtf(player_dir.x * player_dir.x + player_dir.y * player_dir.y) *
        sqrtf(target_dir.x * target_dir.x + target_dir.y * target_dir.y);
    
    if (preangle > 0.0)
    {angle_dir = 0;
     angle_value = acos(preangle);}
    else
    {angle_dir = 1;
    angle_value = acos(-(preangle))}
    
    
    
}
