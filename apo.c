#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strlib.h"

#define ERR_NO_TASKS_FILE -1
#define OK 0

#define TASK_INIT_READ_CAP 16

typedef struct task {
    char *title;
} Task;

void task_print(Task task)
{
    printf("%s\n", task.title);
}

void tasks_print(Task **tasks, unsigned long num_tasks)
{
    for (int i = 0; i < num_tasks; ++i)
    {
        task_print((*tasks)[i]);
    }
}

FILE *ensure_tasks_file_exists()
{
    // TODO: use XDG Base Directory Spec
    // https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html

    char *home = getenv("HOME");
    char *filename = "tasks.txt";

    char buffer[strlen(home) + 1 + strlen("tasks.txt")];
    sprintf(buffer, "%s/%s", getenv("HOME"), filename);

    return fopen(buffer, "r+");
}

unsigned long read_tasks_from_file(FILE *file, Task **tasks)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    unsigned long num_tasks = 0;
    unsigned long cap = TASK_INIT_READ_CAP;

    *tasks = malloc(cap * sizeof(Task));

    while ((read = getline(&line, &len, file)) != -1)
    {
        if (strlen(line) == 0) continue;

        char *trimmed_line = strtrim(line);
        if (trimmed_line == NULL) continue;

        if (num_tasks >= cap)
        {
            // Resize the buffer to 2x capacity
            cap = cap * 2;
            *tasks = realloc(*tasks, cap * sizeof(Task));
        }

        (*tasks)[num_tasks++].title = trimmed_line;
    }

    free(line);
    return num_tasks;
}

int main(int argc, char *argv[])
{
    FILE *file = ensure_tasks_file_exists();

    if (file == NULL)
    {
        printf("Unable to open tasks file: %s\n", strerror(errno));
        return ERR_NO_TASKS_FILE;
    }

    Task *tasks = NULL;
    unsigned long num_tasks = read_tasks_from_file(file, &tasks);

    tasks_print(&tasks, num_tasks);

    // TOOD: free tasks

    fclose(file);

    return OK;
}

