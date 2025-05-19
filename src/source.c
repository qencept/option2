#include "source.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int source_unmarshall(const char *start, source_t *source) {
    if (*start == 'E') {
        if (*(start + 1) != '\0') {
            return -4;
        }
        *source = source_e;
    } else {
        char *end;
        errno = 0;
        const auto value = strtoul(start, &end, 10);
        if (errno == ERANGE) {
            return -1;
        }
        if (end == start || *end != '\0') {
            return -2;
        }
        if (value > source_max) {
            return -3;
        }
        *source = value;
    }
    return 0;
}

void source_marshall(const source_t source, char *source_str) {
    if (source_str != nullptr) {
        source_str[0] = '\0';
        if (source == source_e) {
            strcpy(source_str, "E");
        }
        if (source <= source_max) {
            sprintf(source_str, "%u", source);
        }
    }
}
