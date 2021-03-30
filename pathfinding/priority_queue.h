#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

struct Queue {
    int front, rear;
    unsigned size, capacity;
    struct node** array;
};

struct Queue* createQueue(unsigned capacity);

int isFull_queue(struct Queue* queue);

int isEmpty_queue(struct Queue* queue);

void enqueue(struct Queue* queue, struct node *item);

struct node *dequeue(struct Queue* queue);

struct node *front(struct Queue* queue);

struct node *rear(struct Queue* queue);

int isitin(struct Queue *queue, struct node *item);

void print_queue(struct Queue* queue);

#endif
