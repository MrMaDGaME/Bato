#ifndef GRAPH_H
#define GRAPH_H

struct graph{
    int order;
    struct node *first;
};

struct node{
    struct chkpoint *point;
    struct linklist *links;
    struct node *next;
};

struct linklist{
    struct node *neighbourg;
    struct linklist *next;
};

struct chkpoint{
    int x, y, is_water;
    unsigned int cost, heuristic;
};

struct graph *create_graph();

void add_node(struct graph *g, int x, int y, int is_water);

void add_link(struct node *s1, struct node *s2);

void free_graph(struct graph *g);

#endif
