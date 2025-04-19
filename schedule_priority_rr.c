#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include "cpu.h"
#include "list.h"
#include "schedulers.h"
#include "task.h"

#define TIME_QUANTUM 10

static int task_id = 0;
static struct node* head[] = {NULL, NULL, NULL, NULL, NULL,
                              NULL, NULL, NULL, NULL, NULL};
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
    insert(&head[priority - 1], task);

    // Unlock the mutex after adding the task
    pthread_mutex_unlock(&task_mutex);
}

void schedule() {
    // Lock the mutex to ensure thread safety
    pthread_mutex_lock(&task_mutex);

    // Implement Priority RR scheduling
    // Start from MAX_PRIORITY and work down to MIN_PRIORITY
    for (int priority = MAX_PRIORITY; priority >= MIN_PRIORITY; priority--) {
        // Check if there are tasks in the current priority queue
        while (head[priority - 1] != NULL) {
            struct node* current = head[priority - 1];
            struct task* task = current->task;

            // Execute the task for one time quantum or until completion
            int slice =
                (task->burst < TIME_QUANTUM) ? task->burst : TIME_QUANTUM;
            run(task, slice);
            task->burst -= slice;

            // Check if the task is completed
            if (task->burst <= 0) {
                // If the task is completed, remove it
                delete (&(head[priority - 1]), task);
                free(task);
            } else {
                // Move the task to the end of the queue
                delete (&(head[priority - 1]), task);
                insert(&(head[priority - 1]), task);
            }
        }
    }

    // Unlock the mutex after scheduling
    pthread_mutex_unlock(&task_mutex);
}