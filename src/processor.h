#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdio.h>

#include "flow.h"
#include "source.h"

constexpr int max_count_by_comb = 0x10000;

typedef struct processor_t processor_t;

processor_t *processor_create(FILE *output);

int processor_add_flow_source(processor_t *processor, flow_t flow, source_t source);

void processor_count_combinations(const processor_t *processor);

void processor_free(processor_t *processor);

#endif //PROCESSOR_H
