#include <stdio.h>
#include <unistd.h>
#include "task.h"

void io_task() {
    usleep(500000);  // simulate I/O wait of 0.5 seconds
}
