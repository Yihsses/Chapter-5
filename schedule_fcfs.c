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

    // Unlock the mutex after scheduling
    pthread_mutex_unlock(&task_mutex);
}