#include "processor.h"

#include <stdio.h>
#include <stdlib.h>

#include "comb.h"
#include "hashmap.h"

struct processor_t {
    int adds;
    FILE *output;
    hashmap_t *map;
};

processor_t *processor_create(FILE *output) {
    processor_t *processor = malloc(sizeof(processor_t));
    if (processor == nullptr) {
        return nullptr;
    }

    const auto map = hashmap_create(1024);
    if (map == nullptr) {
        free(processor);
        return nullptr;
    }

    processor->map = map;
    processor->output = output;
    return processor;
}

int processor_add_flow_source(processor_t *processor, const flow_t flow, const source_t source) {
    processor->adds++;
    comb_t old_comb = 0;
    comb_t new_comb = 0;
    const auto map = processor->map;
    hashmap_get(map, flow, &old_comb);
    new_comb = comb_add(old_comb, source);
    if (new_comb != old_comb) {
        if (hashmap_put(map, flow, new_comb) != 0) {
            return -1;
        }
    }
    return 0;
}

void processor_count_combinations(const processor_t *processor) {
    uint32_t count_by_comb[1 << (source_e + 1)] = {0};

    flow_t flow;
    comb_t comb;
    const auto it = hashmap_iter_create(processor->map);
    while (hashmap_iter_next(it, &flow, &comb)) {
        if (count_by_comb[comb] < max_count_by_comb) {
            count_by_comb[comb]++;
        }
    }

    uint32_t total = 0;
    uint32_t unique = 0;
    for (uint32_t c = 0; c < sizeof(count_by_comb) / sizeof(count_by_comb[0]); c++) {
        const auto count = count_by_comb[c];
        if (count > 0) {
            char comb_str[comb_max_length() + 1];
            comb_marshall(c, comb_str);
            fprintf(processor->output, "%s %d\n", comb_str, count);
            total += count;
            unique++;
        }
    }

    fprintf(processor->output, "Processed %d lines, counted %d total %d unique combinations\n",
            processor->adds, total, unique);

    hashmap_iter_free(it);
}

void processor_free(processor_t *processor) {
    hashmap_free(processor->map);
    free(processor);
}
