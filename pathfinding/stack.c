// C program for array implementation of stack
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "graph.h"
#include "stack.h"
 
// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct chkpoint**)malloc(stack->capacity * sizeof(struct chkpoint*));
    return stack;
}
 
// Stack is full when top is equal to the last index
int isFull_stack(struct Stack* stack)
{
  return stack->top == (int)stack->capacity - 1;
}
 
// Stack is empty when top is equal to -1
int isEmpty_stack(struct Stack* stack)
{
    return stack->top == -1;
}
 
// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, struct chkpoint *item)
{
    if (isFull_stack(stack))
        return;
    stack->array[++stack->top] = item;
}
 
// Function to remove an item from stack.  It decreases top by 1
struct chkpoint *pop(struct Stack* stack)
{
    if (isEmpty_stack(stack))
      errx(1, "can't pop : empty stack");
    return (stack->array[stack->top--]);
}
 
// Function to return the top from stack without removing it
struct chkpoint *peek(struct Stack* stack)
{
    if (isEmpty_stack(stack))
      errx(1, "can't pop : empty stack");
    return (stack->array[stack->top]);
}

void print_stack(struct Stack *stack){
  int i = 0;
  printf("[");
  while(i != stack->top + 1){
    printf("x = %d, y = %d; ", stack->array[i]->x, stack->array[i]->y);
    i++;
  }
  printf("]\n");
}
 
// Driver program to test above functions
/*int main()
{
    struct Stack* stack = createStack(100);

    struct chkpoint chk1 = {0,0,0,0,1};
    struct chkpoint chk2 = {0,0,0,0,2};
    struct chkpoint chk3 = {0,0,0,0,3};
    struct chkpoint chk4 = {0,0,0,0,4};
    struct chkpoint chk5 = {0,0,0,0,5};
 
    push(stack, &chk1);
    push(stack, &chk2);
    push(stack, &chk3);
    push(stack, &chk4);
    push(stack, &chk5);
 
    printf("%d popped from stack\n", pop(stack)->heuristic);
    free(stack->array);
    free(stack);
 
    return 0;
    }*/
