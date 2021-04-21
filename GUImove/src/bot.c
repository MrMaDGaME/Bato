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
    
}