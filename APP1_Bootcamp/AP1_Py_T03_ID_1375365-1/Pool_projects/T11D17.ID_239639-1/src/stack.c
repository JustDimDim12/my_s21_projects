#include "stack.h"

#include <stdlib.h>

Stack* init() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack != NULL) {
        stack->top = NULL;
    }
    return stack;
}

int push(Stack* stack, int data) {
    int result = FAIL;

    if (stack != NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode != NULL) {
            newNode->data = data;
            newNode->next = stack->top;
            stack->top = newNode;
            result = SUCCESS;
        }
    }

    return result;
}

int pop(Stack* stack, int* data) {
    int result = FAIL;

    if (stack != NULL && stack->top != NULL && data != NULL) {
        Node* temp = stack->top;
        *data = temp->data;
        stack->top = temp->next;
        free(temp);
        result = SUCCESS;
    }

    return result;
}

void destroy(Stack* stack) {
    if (stack != NULL) {
        Node* cur = stack->top;
        while (cur != NULL) {
            Node* next = cur->next;
            free(cur);
            cur = next;
        }
        free(stack);
    }
}