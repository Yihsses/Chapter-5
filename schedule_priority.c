#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include "cpu.h"
#include "list.h"
#include "schedulers.h"
#include "task.h"

static int task_id = 0;
static struct node* head = NULL;
static pthread_mutex_t task_mutex = PTHREAD_MUTEX_INITIALIZER;

void add(char* name, int priority, int burst) {
    // Lock the mutex to ensure thread safety
    pthread_mutex_lock(&task_mutex);

    // Create a new task
    struct task* task = malloc(sizeof(struct task));
    task->name = name;
    task->priority = priority;
    task->burst = burst;
    task->tid = task_id++;

    // insert the node at the end of the list
    insert(&head, task);

    // Unlock the mutex after adding the task
    pthread_mutex_unlock(&task_mutex);
}

void schedule() {
    // Lock the mutex to ensure thread safety
    pthread_mutex_lock(&task_mutex);

    // Implement Priority scheduling
    while (head != NULL) {
        // Find the task with the highest priority
        struct node* current = head;
        struct node* highest_priority = head;
        while (current != NULL) {
            if (current->task->priority > highest_priority->task->priority)
                highest_priority = current;
            current = current->next;
        }

        // Execute the highest priority task
        run(highest_priority->task, highest_priority->task->burst);

        // Remove the task from the list
        struct node* temp = highest_priority;
        delete (&head, temp->task);

        // Free the task and node
        free(temp->task);
        free(temp);
    }

    // Unlock the mutex after scheduling
    pthread_mutex_unlock(&task_mutex);
}