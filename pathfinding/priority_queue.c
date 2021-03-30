// C program for array implementation of queue
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "graph.h"
#include "priority_queue.h"

#define QUEUE_SIZE 50

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
    queue->array = (struct node**)malloc(
        queue->capacity * sizeof(struct node*));
    return queue;
}

// Queue is full when size becomes
// equal to the capacity
int isFull_queue(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
int isEmpty_queue(struct Queue* queue)
{
    return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, struct node *item)
{
  
  if (isFull_queue(queue))
    errx(1, "can't enqueue : full queue");
  queue->rear = (queue->rear + 1) % queue->capacity;
  int enqindex = queue->front;
  while (enqindex != queue->rear && queue->array[enqindex]->point->heuristic < item->point->heuristic){
    enqindex = (enqindex + 1) % queue->capacity;
  }
  int i = queue->rear;
  while (i != enqindex - 1 && (enqindex != 0 || i != (int)(queue->capacity - 1))){
    if (i == 0){
      queue->array[i] = queue->array[queue->capacity - 1];
    }
    else{
      queue->array[i] = queue->array[i - 1];
    }
    i--;
    while (i < 0){
      i += queue->capacity;
    }
  }
  queue->array[enqindex] = item;
  
  queue->size = queue->size + 1;
}

// Function to remove an item from queue.
// It changes front and size
struct node *dequeue(struct Queue* queue)
{
    if (isEmpty_queue(queue))
        errx(1, "can't dequeue : empty queue");
    struct node *item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function to get front of queue
struct node *front(struct Queue* queue)
{
    if (isEmpty_queue(queue))
        errx(1, "can't get front : empty queue");
    return queue->array[queue->front];
}

// Function to get rear of queue
struct node *rear(struct Queue* queue)
{
    if (isEmpty_queue(queue))
        errx(1, "can't get rear : empty queue");
    return queue->array[queue->rear];
}

int isitin(struct Queue *queue, struct node *item){
  unsigned i = 0;
  while(i<queue->size){
    if(queue->array[(queue->front + i) % queue->capacity] == item){
      return 1;
    }
    i++;
  }
  return 0;
}

void print_queue(struct Queue* queue){
    printf("[");
    for (size_t i = 0; i < queue->size; i++)
    {
        printf("%f;", queue->array[(queue->front + i) % queue->capacity]->point->heuristic);
    }
    printf("]\n");
}

void print_array(struct Queue* queue){
  printf("[");
    for (size_t i = 0; i < QUEUE_SIZE; i++)
    {
        printf("%f;", queue->array[i]->point->heuristic);
    }
    printf("]\n");
}

// Driver program to test above functions./
/*int main()
{
  struct Queue* queue = createQueue(QUEUE_SIZE);
  struct chkpoint chk1 = {0,0,0,0,1};
  struct chkpoint chk2 = {0,0,0,0,2};
  struct chkpoint chk3 = {0,0,0,0,3};
  struct chkpoint chk4 = {0,0,0,0,4};
  struct chkpoint chk5 = {0,0,0,0,5};

  struct node n1 = {&chk1, NULL, NULL, 0};
  struct node n2 = {&chk2, NULL, NULL, 0};
  struct node n3 = {&chk3, NULL, NULL, 0};
  struct node n4 = {&chk4, NULL, NULL, 0};
  struct node n5 = {&chk5, NULL, NULL, 0};

  enqueue(queue, &n2);
  print_queue(queue);
  enqueue(queue, &n5);
  print_queue(queue);
  enqueue(queue, &n3);
  print_queue(queue);
  enqueue(queue, &n1);
  print_queue(queue);
  enqueue(queue, &n4);
  print_queue(queue);
    
  printf("heuristic = %f\n", dequeue(queue)->point->heuristic);
  print_queue(queue);
  printf("heuristic = %f\n", dequeue(queue)->point->heuristic);
  print_queue(queue);
  enqueue(queue, &n4);
  print_queue(queue);
  enqueue(queue, &n5);
  print_queue(queue);
  printf("isitin1 = %d\n", isitin(queue, &n1));
  printf("isitin5 = %d\n", isitin(queue, &n5));
    
  free(queue->array);
  free(queue);

  return 0;
  }*/

