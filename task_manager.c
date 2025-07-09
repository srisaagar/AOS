#include <stdio.h>
#include <pthread.h>
#include "tasks/task.h"
#include "utils/timer.h"

#define NUM_TASKS 4

typedef struct {
    char* name;
    void (*func)();
    long exec_time_ms;
} Task;

Task tasks[NUM_TASKS] = {
    {"CPU Task 1", cpu_task, 0},
    {"I/O Task 1", io_task, 0},
    {"CPU Task 2", cpu_task, 0},
    {"I/O Task 2", io_task, 0}
};

void* run_task(void* arg) {
    Task* t = (Task*)arg;
    long start = current_time_ms();
    t->func();
    long end = current_time_ms();
    t->exec_time_ms = end - start;
    return NULL;
}

void run_all_tasks() {
    pthread_t threads[NUM_TASKS];
    long total_cpu = 0, total_io = 0;

    for (int i = 0; i < NUM_TASKS; i++) {
        pthread_create(&threads[i], NULL, run_task, &tasks[i]);
    }

    for (int i = 0; i < NUM_TASKS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n--- Execution Breakdown ---\n");
    for (int i = 0; i < NUM_TASKS; i++) {
        printf("%s took %ld ms\n", tasks[i].name, tasks[i].exec_time_ms);
        if (strstr(tasks[i].name, "CPU")) total_cpu += tasks[i].exec_time_ms;
        else total_io += tasks[i].exec_time_ms;
    }

    printf("\n--- CPU vs I/O Time ---\n");
    printf("Total CPU time: %ld ms\n", total_cpu);
    printf("Total I/O time: %ld ms\n", total_io);
}
