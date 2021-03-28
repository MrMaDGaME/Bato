#ifndef STACK_H
#define STACK_H

// A structure to represent a stack
struct Stack {
    int top;
    unsigned capacity;
    struct chkpoint** array;
};

struct Stack* createStack(unsigned capacity);

int isFull_stack(struct Stack* stack);

int isEmpty_stack(struct Stack* stack);

void push(struct Stack* stack, struct chkpoint *item);

struct chkpoint *pop(struct Stack* stack);

struct chkpoint *peek(struct Stack* stack);

void print_stack(struct Stack *stack);

#endif
