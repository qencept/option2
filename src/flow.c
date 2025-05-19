#include "flow.h"

#include <errno.h>
#include <stdlib.h>

int flow_unmarshall(const char *start, flow_t *flow) {
    char *end;
    errno = 0;
    const auto value = strtoul(start, &end, 10);
    if (errno == ERANGE) {
        return -1;
    }
    if (end == start || *end != '\0') {
        return -2;
    }
    if (value > flow_max) {
        return -3;
    }
    *flow = value;
    return 0;
}
