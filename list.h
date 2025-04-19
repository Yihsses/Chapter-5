#ifndef LIST_H
#define LIST_H

#include "task.h"

struct node {
    struct task* task;
    struct node* next;
};

void insert(struct node** head, struct task* task);
void delete(struct node** head, struct task* task);
void traverse(struct node* head);

#endif  // LIST_H
