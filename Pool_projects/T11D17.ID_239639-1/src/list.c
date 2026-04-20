#include "list.h"

#include <stdlib.h>

#include "door_struct.h"

struct node* init(struct door* door) {
    struct node* root = NULL;
    root = (struct node*)malloc(sizeof(struct node));
    if (root != NULL) {
        root->door = door;
        root->next = NULL;
    }
    return root;
}

struct node* add_door(struct node* elem, struct door* door) {
    struct node* new_node = NULL;

    if (elem != NULL && door != NULL) {
        new_node = (struct node*)malloc(sizeof(struct node));
        if (new_node != NULL) {
            new_node->door = door;
            new_node->next = elem->next;
            elem->next = new_node;
        }
    }
    return new_node;
}

// struct node* find_door(int door_id, struct node* root) {
//     struct node* result = NULL;
//     struct node* current = root;

//     while (current != NULL && result == NULL) {
//         if (current->door->id == door_id) {
//             result = current;
//         }
//         current = current->next;
//     }
//     return result;
// }

struct node* remove_door(struct node* elem, struct node* root) {
    struct node* result = root;

    if (root != NULL && elem != NULL) {
        if (root == elem) {
            result = root->next;
            free(root);
        } else {
            struct node* cur = root;
            while (cur->next != NULL && cur->next != elem) {
                cur = cur->next;
            }
            if (cur->next == elem) {
                cur->next = elem->next;
                free(elem);
            }
        }
    }
    return result;
}

void destroy(struct node* root) {
    while (root != NULL) {
        struct node* temp = root;
        root = root->next;
        free(temp);
    }
}