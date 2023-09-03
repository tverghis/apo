#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strlib.h"
#include "tasks.h"

#define ERR_NO_TASKS_FILE -1
#define OK 0

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

Tasks read_tasks_from_file(FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    Tasks tasks = Tasks_new();

    while ((read = getline(&line, &len, file)) != -1)
    {
        if (strlen(line) == 0) continue;

        char *trimmed_line = strtrim(line);
        if (trimmed_line == NULL) continue;

        Tasks_add_task(&tasks, trimmed_line);
    }

    free(line);

    return tasks;
}

int main(int argc, char *argv[])
{
    FILE *file = ensure_tasks_file_exists();

    if (file == NULL)
    {
        printf("Unable to open tasks file: %s\n", strerror(errno));
        return ERR_NO_TASKS_FILE;
    }

    Tasks tasks = read_tasks_from_file(file);
    Tasks_print(&tasks);

    Tasks_free(&tasks);
    fclose(file);

    return OK;
}

