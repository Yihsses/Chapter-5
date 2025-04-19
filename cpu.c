#include "cpu.h"
#include <stdio.h>
#include "task.h"

void run(struct task* task, int slice) {
    printf("Running task = [%s] [%d] [%d] for %d units.\n", task->name,
           task->priority, task->burst, slice);
}
