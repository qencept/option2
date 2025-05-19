#ifndef CSV_H
#define CSV_H

#include "flow.h"
#include "processor.h"
#include "source.h"

typedef int (*csv_callback)(processor_t *processor, flow_t flow, source_t source);

int csv_parse(const char *filename, csv_callback cb, processor_t *processor);

#endif //CSV_H
