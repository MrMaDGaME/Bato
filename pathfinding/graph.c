#include <stdlib.h>
#include "graph.h"

#define HEIGHT 9
#define WIDTH 16
#define PIXEL_SIZE 10


struct graph *create_graph(){
    struct graph *g = malloc(sizeof(struct graph));
    g->order = 0;
    g->first = NULL;
    for (int j = 0; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            add_node(g, i * PIXEL_SIZE, j * PIXEL_SIZE, 1);
            g->order++;
            if (i){
                add_link(g->first, g->first->next);
            }
	    if (j){
	      struct node *parkour = g->first;
	      for (int k = 0; k < WIDTH - 1; k++)
		{
		  parkour = parkour->next;
		}
	      if (i != WIDTH - 1){
                add_link(g->first, parkour);
	      }
	      parkour = parkour->next;
	      add_link(g->first, parkour);
	      parkour = parkour->next;
	      if (i){
                add_link(g->first, parkour);
	      }
	    }
        }
    }
    return g;
}

void add_node(struct graph *g, int x, int y, int is_water){
    struct chkpoint *point = malloc(sizeof(struct chkpoint));
    point->x = x;
    point->y = y;
    point->is_water = is_water;
    point->cost = 0;
    point->heuristic = 0;
    struct node *s = malloc(sizeof(struct node));
    s->marked = 0;
    s->parent = NULL;
    s->links = NULL;
    s->point = point;
    s->next = g->first;
    g->first = s;
}

void add_link(struct node *s1, struct node *s2){
    // structure qui contient l'arc allant de s1 vers s2
    struct linklist *s2link = malloc(sizeof(struct linklist));
    // définition du voisin
    s2link->neighbourg = s2;
    // ajout de l'arc à la liste chainée de s1
    s2link->next = s1->links;
    s1->links = s2link;

    // réitération dans l'autre sens
    // pour avoir le le lien dans les deux listes d'adjacence
    struct linklist *s1link = malloc(sizeof(struct linklist));
    s1link->neighbourg = s1;
    s1link->next = s2->links;
    s2->links = s1link;
}

void free_graph(struct graph *g){
    struct node *iter = g->first;
    struct node *temp = iter;
    while (iter != NULL){
        free(iter->point);
        struct linklist *iter1 = iter->links;
        struct linklist *temp1 = iter1;
        while (iter1 != NULL){
            temp1 = iter1->next;
            free(iter1);
            iter1 = temp1;
        }
        temp = iter->next;
        free(iter);
        iter = temp;
    }
    free(g);
}

/*int main(){
    struct graph *g = create_graph();
    free_graph(g);
    return 0;
    }*/
