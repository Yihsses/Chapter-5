#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"

void insert(struct node** head, struct task* task) {
    struct node* node = malloc(sizeof(struct node));
    printf("Adding task: %s, Priority: %d, Burst: %d\n", task->name,
           task->priority, task->burst);
    node->task = task;
    node->next = NULL;
    struct node** temp = head;
    while (*temp != NULL)
        temp = &((*temp)->next);
    *temp = node;
}

void delete(struct node** head, struct task* task) {
    struct node *temp, *prev;
    temp = *head;
    if (strcmp(task->name, temp->task->name) == 0) {
        *head = (*head)->next;
    } else {
        prev = *head;
        temp = temp->next;
        while (strcmp(task->name, temp->task->name) != 0) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
    }
}

void traverse(struct node* head) {
    struct node* temp = head;
    while (temp != NULL) {
        printf("[%s] [%d] [%d]\n", temp->task->name, temp->task->priority,
               temp->task->burst);
        temp = temp->next;
    }
}
