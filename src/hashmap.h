#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdint.h>
#include <stdio.h>

constexpr size_t load_factor_numerator = 3;
constexpr size_t load_factor_denominator = 4;

typedef struct hashmap_t hashmap_t;
typedef struct hashmap_iter_t hashmap_iter_t;

hashmap_t *hashmap_create(size_t initial_capacity);

int hashmap_put(hashmap_t *map, uint32_t key, uint32_t value);

void hashmap_get(const hashmap_t *map, uint32_t key, uint32_t *value);

void hashmap_free(hashmap_t *map);

hashmap_iter_t *hashmap_iter_create(const hashmap_t *map);

bool hashmap_iter_next(hashmap_iter_t *it, uint32_t *key, uint32_t *value);

void hashmap_iter_free(hashmap_iter_t *it);

#endif // HASHMAP_H
