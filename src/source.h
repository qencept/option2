#ifndef SOURCE_H
#define SOURCE_H

#include <stdint.h>

// source [0..15,'E']
constexpr int source_max = 15;
constexpr int source_e = source_max + 1;

typedef uint8_t source_t;

int source_unmarshall(const char *start, source_t *source);

void source_marshall(source_t source, char *source_str);

#endif //SOURCE_H
