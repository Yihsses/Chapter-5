#ifndef TASK_H
#define TASK_H

struct task {
    char* name;
    int tid;
    int priority;
    int burst;
};

#endif // TASK_H
