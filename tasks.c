#include <stdio.h>
#include <stdlib.h>

#include "tasks.h"

Tasks Tasks_new()
{
    void *items = malloc(TASKS_INIT_CAPACITY * sizeof(Task));
    Tasks tasks = {.items=items, .cap=TASKS_INIT_CAPACITY, .len=0};
    return tasks;
}

void Tasks_add_task(Tasks *tasks, char *title)
{
    if (tasks->len >= tasks->cap)
    {
        tasks->cap = tasks->cap * 2;
        tasks->items = realloc(tasks->items, tasks->cap * sizeof(Task));
    }

    tasks->items[tasks->len].title = title;
    tasks->len++;
}

void Tasks_free(Tasks *tasks)
{
    for (size_t i = 0; i < tasks->len; ++i)
    {
        free(tasks->items[i].title);
    }

    free(tasks->items);
}

void Tasks_print(Tasks *tasks)
{
    for (int i = 0; i < tasks->len; ++i)
    {
        printf("%s\n", tasks->items[i].title);
    }
}
