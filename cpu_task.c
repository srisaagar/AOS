#include <stdio.h>
#include "task.h"

void cpu_task() {
    volatile long sum = 0;
    for (long i = 0; i < 100000000; i++) {
        sum += i % 5;
    }
}
