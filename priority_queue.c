// C program for array implementation of queue
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "chekpoint.c"
 
// A structure to represent a queue
struct Queue {
    int front, rear, size;
    unsigned capacity;
    struct chkpoint* array;
};
 
// function to create a queue
// of given capacity.
// It initializes size of queue as 0
struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(
        sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
 
    // This is important, see the enqueue
    queue->rear = capacity - 1;
    queue->array = (struct chkpoint*)malloc(
        queue->capacity * sizeof(struct chkpoint));
    return queue;
}
 
// Queue is full when size becomes
// equal to the capacity
int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}
 
// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}
 
// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, struct chkpoint item)
{
    if (isFull(queue))
        errx(1, "can't enqueue : full queue");
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    int i = 0;
    while (i < queue->capacity && queue->array[(queue->rear - i) % queue->capacity]->heuristic > item->heuristic){
        i++;
    }
    int lag = i;
    while (i>0){
        queue->array[(queue->rear - lag + i) % queue->capacity] = queue->array[(queue->rear - lag + i - 1) % queue->capacity];
        i--;
    }
    queue->array[(queue->rear - lag) % queue->capacity] = item;
    queue->size = queue->size + 1;
    printf("%d enqueued to queue\n", item);
}
 
// Function to remove an item from queue.
// It changes front and size
struct chkpoint dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        errx(1, "can't dequeue : empty queue");
    struct chkpoint item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}
 
// Function to get front of queue
struct chkpoint front(struct Queue* queue)
{
    if (isEmpty(queue))
        errx(1, "can't get front : empty queue");
    return queue->array[queue->front];
}
 
// Function to get rear of queue
struct chkpoint rear(struct Queue* queue)
{
    if (isEmpty(queue))
        errx(1, "can't get rear : empty queue");
    return queue->array[queue->rear];
}

void print_queue(struct Queue* queue){
    printf("[");
    for (size_t i = 0; i < queue->size; i++)
    {
        printf("%u;", queue->array[(queue->front + i) % queue->capacity]->heuristic);
    }
    printf("]");
}
 
// Driver program to test above functions./
int main()
{
    struct Queue* queue = createQueue(1000);
 
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
 
    printf("%d dequeued from queue\n\n",
           dequeue(queue));
 
    printf("Front item is %d\n", front(queue));
    printf("Rear item is %d\n", rear(queue));
 
    return 0;
}

