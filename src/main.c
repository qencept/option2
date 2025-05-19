#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "comb.h"
#include "csv.h"
#include "hashmap.h"
#include "processor.h"

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <csv_file>\n", argv[0]);
        return 1;
    }

    const auto processor = processor_create(stdout);
    if (processor == nullptr) {
        fprintf(stderr, "Error: Failed to create processor\n");
        return 2;
    }

    if (csv_parse(argv[1], processor_add_flow_source, processor) != 0) {
        fprintf(stderr, "Error: Failed to parse file\n");
        processor_free(processor);
        return 3;
    }

    processor_count_combinations(processor);
    processor_free(processor);
    return 0;
}
