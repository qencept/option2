#include "csv.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void clean_trail(char *end) {
    do {
        *end = '\0';
    } while (isspace(*--end));
}

int csv_parse(const char *filename, const csv_callback cb, processor_t *processor) {
    if (!filename || !cb) {
        return -1;
    }

    FILE *f = fopen(filename, "r");
    if (!f) {
        return -2;
    }

    char *line = nullptr;
    size_t size = 0;
    while (getline(&line, &size, f) != -1) {
        const auto start0 = line;
        const auto delimiter0 = strchrnul(start0, ',');
        clean_trail(delimiter0);

        const auto start1 = delimiter0 + 1;
        const auto delimiter1 = strchrnul(start1, ',');
        clean_trail(delimiter1);

        flow_t flow;
        source_t source;
        if (flow_unmarshall(start0, &flow) == 0 && source_unmarshall(start1, &source) == 0) {
            if (cb(processor, flow, source) != 0) {
                free(line);
                fclose(f);
                return -3;
            }
        }
    }

    if (line) {
        free(line);
    }
    fclose(f);

    return 0;
}
