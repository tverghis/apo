#ifndef TASKS_H
#define TASKS_H

#define TASKS_INIT_CAPACITY 16

#include <unistd.h>

typedef struct task {
    char *title;
} Task;

typedef struct tasks {
    Task *items;
    size_t cap;
    size_t len;
} Tasks;

Tasks Tasks_new();
void Tasks_add_task(Tasks *tasks, char *title);
void Tasks_free(Tasks *tasks);
void Tasks_print(Tasks *tasks);

#endif // TASKS_H


