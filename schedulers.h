#ifndef SCHEDULERS_H
#define SCHEDULERS_H

#include "list.h"
#include <stddef.h>

#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

void add(char *name, int priority, int burst);
void schedule();

#endif  // SCHEDULERS_H
