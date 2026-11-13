#include "list.h"

#include <stdio.h>
#include <stdlib.h>

#include "door_struct.h"

char* add_door_test() {
    struct door door1 = {1, 0};
    struct door door2 = {2, 0};
    char* res = "SUCCESS";
    struct node* root = NULL;
    struct node* new = NULL;

    root = init(&door1);
    if (root != NULL) {
        new = add_door(root, &door2);
        if (new == NULL || root->next != new || new->door != &door2) {
            res = "FAIL";
        }
    } else {
        res = "FAIL";
    }

    destroy(root);
    return res;
}

char* remove_door_test() {
    struct door door1 = {1, 0};
    struct door door2 = {2, 0};
    char* res = "SUCCESS";
    struct node* root = NULL;
    struct node* new = NULL;

    root = init(&door1);
    if (root != NULL) {
        new = add_door(root, &door2);
        if (new != NULL) {
            root = remove_door(new, root);
            if (root->next != NULL) {
                res = "FAIL";
            }
        } else {
            res = "FAIL";
        }
    } else {
        res = "FAIL";
    }

    destroy(root);
    return res;
}

int main() {
    printf("%s\n", add_door_test());
    printf("%s\n", remove_door_test());
    return 0;
}