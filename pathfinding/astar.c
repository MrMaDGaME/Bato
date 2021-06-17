#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <math.h>
#include "graph.h"
#include "priority_queue.h"
#include "stack.h"
#include "astar.h"

#define HEIGHT 76
#define WIDTH 114

struct Stack *pathfinding(struct node *start, struct node *end){
  if(!start){
    return NULL;
  }

  struct Stack *path = createStack(2 * (HEIGHT + WIDTH));
  struct Queue *queue = createQueue(HEIGHT * WIDTH);

  enqueue(queue, start);

  while(!isEmpty_queue(queue)){
    struct node *u = dequeue(queue);
    if(u->point->x == end->point->x && u->point->y == end->point->y){
      while(u != start){
        push(path, u->point);
        u = u->parent;
      }

      push(path, start->point);
      free(queue->array);
      free(queue);
      return path;
    }

    struct linklist *adjlist = u->links;
    while (adjlist){
      struct node *adj = adjlist->neighbourg;
      if(!(!adj->point->is_water || adj->marked || isitin(queue, adj))){
        adj->point->cost = u->point->cost + 1;
        adj->point->heuristic = adj->point->cost 
                              + (sqrtf(pow((float)adj->point->x - end->point->x, 2) 
                              + pow((float)adj->point->y - end->point->y, 2)))/10;
                              
        adj->parent = u;
        enqueue(queue, adj);
      }
      adjlist = adjlist->next;
    }
    u->marked = 1;
  }

  free(path->array);
  free(path);
  free(queue->array);
  free(queue);
  errx(1, "pathfinding : can't find path");
}

/*int main(){
  struct graph *map = create_graph();
  struct node *start = map->first;
  struct node *end;
  struct node *parkour = start;
  while(parkour != NULL){
    if(parkour->point->x == 20 && parkour->point->y == 50){
      end = parkour;
    }
    if(parkour->point->x == 120 && (parkour->point->y == 60 || parkour->point->y == 70 || parkour->point->y == 80)){
      parkour->point->is_water = 0;
    }
    if(parkour->point->x == 80 && parkour->point->y <= 70){
      parkour->point->is_water = 0;
    }
    if(parkour->point->x == 50 && parkour->point->y >= 40){
      parkour->point->is_water = 0;
    }
    printf("parkour : x = %d, y = %d, is_water = %d\n", parkour->point->x, parkour->point->y, parkour->point->is_water);
    parkour = parkour->next;
  }
  printf("start : x = %d, y = %d\n", start->point->x, start->point->y);
  printf("end : x = %d, y = %d\n", end->point->x, end->point->y);
  struct Stack *path = pathfinding(start, end);
  print_stack(path);
  free_graph(map);
  free(path->array);
  free(path);
  return 1;
  }
*/
