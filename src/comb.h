#ifndef COMB_H
#define COMB_H

#include <stdint.h>
#include <stdio.h>

#include "source.h"

typedef uint32_t comb_t;

comb_t comb_add(comb_t comb, source_t source);

void comb_marshall(comb_t comb, char *comb_str);

size_t comb_max_length();

#endif //COMB_H
