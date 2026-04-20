#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

int push_test() {
    int res = SUCCESS;
    Stack* stack = init();

    if (stack == NULL) {
        res = FAIL;
    } else {
        if (push(stack, 10) != SUCCESS) {
            res = FAIL;
        } else if (stack->top == NULL || stack->top->data != 10) {
            res = FAIL;
        }
    }

    destroy(stack);
    return res;
}

int pop_test() {
    int res = SUCCESS;
    Stack* stack = init();
    int data;

    if (stack == NULL) {
        res = FAIL;
    } else {
        if (push(stack, 20) != SUCCESS || push(stack, 30) != SUCCESS) {
            res = FAIL;
        } else if (pop(stack, &data) != SUCCESS || data != 30) {
            res = FAIL;
        } else if (pop(stack, &data) != SUCCESS || data != 20) {
            res = FAIL;
        } else if (pop(stack, &data) != FAIL) {
            res = FAIL;
        }
    }

    destroy(stack);
    return res;
}

int main() {
    printf("%s\n", push_test() == SUCCESS ? "SUCCESS" : "FAIL");
    printf("%s\n", pop_test() == SUCCESS ? "SUCCESS" : "FAIL");
    return 0;
}