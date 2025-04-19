#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "schedulers.h"
#include "task.h"

#define SIZE 1024

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the input file and parse the tasks
    FILE* file = fopen(argv[1], "r");
    char buffer[SIZE];
    while (fgets(buffer, SIZE, file) != NULL) {
        char* task = strdup(buffer);
        char* name = strsep(&task, ",");
        int priority = atoi(strsep(&task, ","));
        int burst = atoi(strsep(&task, ","));
        add(name, priority, burst);
        free(task);
    }
    fclose(file);

    // Invoke the scheduler
    schedule();

    return 0;
}