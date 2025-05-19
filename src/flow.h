#ifndef FLOW_H
#define FLOW_H

#include <stdint.h>

// flow [0..0xffffffff]
constexpr unsigned long flow_max = UINT32_MAX;

typedef uint32_t flow_t;

int flow_unmarshall(const char *start, flow_t *flow);

#endif //FLOW_H
