#include "comb.h"

#include <stdlib.h>
#include <string.h>

comb_t comb_add(comb_t comb, const source_t source) {
    return comb | 1 << source;
}

void comb_marshall(const comb_t comb, char *comb_str) {
    comb_str[0] = '\0';
    comb_str = strcat(comb_str, "(");
    bool first = true;
    for (source_t source = 0; source <= source_e; source++) {
        if (comb & 1 << source) {
            if (first) {
                first = false;
            } else {
                comb_str = strcat(comb_str, ",");
            }
            char source_str[3];
            source_marshall(source, source_str);
            comb_str = strcat(comb_str, source_str);
        }
    }
    comb_str = strcat(comb_str, ")");
}

size_t comb_max_length() {
    size_t length = 0;
    length++; // '('
    for (int i = 0; i < 10; i++) {
        length += 2; // "x,"
    }
    for (int i = 10; i <= source_max; i++) {
        length += 3; // "xy,"
    }
    length++; // 'E'
    length++; // ')'
    return length;
}
