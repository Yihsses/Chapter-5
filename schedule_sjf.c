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
    // Implement Shortest Job First (SJF) scheduling
    while (head != NULL) {
        // Find the task with the shortest burst time
        struct node* current = head;
        struct node* shortest = head;
        while (current != NULL) {
            if (current->task->burst < shortest->task->burst)
                shortest = current;
            current = current->next;
        }

        // Execute the shortest job
        run(shortest->task, shortest->task->burst);

        // Remove the task from the list
        struct node* temp = shortest;
        delete (&head, temp->task);

        // Free the task and node
        free(temp->task);
        free(temp);
    }
}