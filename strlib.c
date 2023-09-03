#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "strlib.h"

char *strtrim(char *str)
{
    if (str == NULL)
    {
        return NULL;
    }

    size_t len = strlen(str);

    char *left = str;
    char *right = str + len - 1;

    while (isspace(*left) || isspace(*right)) {
        if (isspace(*left)) left++;
        if (isspace(*right)) right--;
    }

    size_t new_str_len = right - left + 1;

    size_t buf_size = new_str_len + 1; // +1 for `\0`
    if (buf_size <= 0) return NULL;

    char *new_str = malloc(buf_size);

    memcpy(new_str, left, new_str_len);
    new_str[new_str_len] = '\0';

    return new_str;
}

