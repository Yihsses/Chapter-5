#ifndef CPU_H
#define CPU_H

#include "task.h"
#define QUANTUM 10

void run(struct task* task, int slice);

#endif  // CPU_H
