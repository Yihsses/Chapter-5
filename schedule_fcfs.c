#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include "cpu.h"
#include "list.h"
#include "schedulers.h"
#include "task.h"

static int task_id = 0;
static struct node* head = NULL;

void add(char* name, int priority, int burst) {
    // Create a new task
    struct task* task = malloc(sizeof(struct task));
    task->name = name;
    task->priority = priority;
    task->burst = burst;
    task->tid = task_id++;

    // insert the node at the end of the list
    insert(&head, task);
}

void schedule() {
    // Simulate First-Come, First-Served (FCFS) scheduling
    struct node* current = head;
    while (current != NULL) {
        // Simulate the task execution
        run(current->task, current->task->burst);

        // Remove the task from the list
        delete (&head, current->task);

        // Free the node and task and move to the next node
        free(current->task);
        struct node* tmp = current;
        current = current->next;
        free(tmp);
    }
}