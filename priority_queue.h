#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

struct Queue {
    int front, rear;
    unsigned size, capacity;
    struct chkpoint* array;
};

struct Queue* createQueue(unsigned capacity);

int isFull(struct Queue* queue);

int isEmpty(struct Queue* queue);

void enqueue(struct Queue* queue, struct chkpoint item);

struct chkpoint dequeue(struct Queue* queue);

struct chkpoint front(struct Queue* queue);

struct chkpoint rear(struct Queue* queue);

void print_queue(struct Queue* queue);

#endif
