#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include "cpu.h"
#include "list.h"
#include "schedulers.h"
#include "task.h"

#define TIME_QUANTUM 10

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

    // Round Robin scheduling
    while (head != NULL) {
        struct node* current = head;
        struct task* task = current->task;

        // Execute the task for one time quantum or until completion
        int slice = (task->burst < TIME_QUANTUM) ? task->burst : TIME_QUANTUM;
        run(task, slice);
        task->burst -= slice;

        // Check if the task is completed
        if (task->burst <= 0) {
            // If the task is completed, remove it
            delete (&head, task);
            free(task);
            free(current);
        } else {
            // Move the task to the end of the queue
            delete (&head, task);
            insert(&head, task);
        }
    }

    // Unlock the mutex after scheduling
    pthread_mutex_unlock(&task_mutex);
}