#ifndef STACK_H
#define STACK_H

#define SUCCESS 0
#define FAIL 1

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

Stack* init();
int push(Stack* stack, int data);
int pop(Stack* stack, int* data);
void destroy(Stack* stack);

#endif