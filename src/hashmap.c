#include "hashmap.h"
#include <stdlib.h>

typedef struct node_t {
    uint32_t key;
    uint32_t value;
    struct node_t *next;
} node_t;

struct hashmap_t {
    node_t **buckets;
    size_t capacity;
    size_t size;
};

struct hashmap_iter_t {
    const hashmap_t *map;
    size_t index;
    node_t *node;
};

static uint32_t hash(const uint32_t key, const size_t capacity) {
    return key * 2654435761U % capacity;
}

hashmap_t *hashmap_create(const size_t initial_capacity) {
    const auto map = (hashmap_t *) malloc(sizeof(hashmap_t));
    if (map == nullptr) {
        return nullptr;
    }

    const auto buckets = (node_t **) calloc(initial_capacity, sizeof(node_t *));
    if (buckets == nullptr) {
        free(map);
        return nullptr;
    }

    map->size = 0;
    map->buckets = buckets;
    map->capacity = initial_capacity;
    return map;
}

static bool hashmap_resize(hashmap_t *map, const size_t new_capacity) {
    if (new_capacity <= map->capacity) {
        return true;
    }

    const auto new_buckets = (node_t **) calloc(new_capacity, sizeof(node_t *));
    if (new_buckets == nullptr) {
        return false;
    }

    for (size_t i = 0; i < map->capacity; i++) {
        node_t *node = map->buckets[i];
        while (node) {
            node_t *next = node->next;
            uint32_t new_index = hash(node->key, new_capacity);
            node->next = new_buckets[new_index];
            new_buckets[new_index] = node;
            node = next;
        }
    }

    free(map->buckets);
    map->buckets = new_buckets;
    map->capacity = new_capacity;
    return true;
}

int hashmap_put(hashmap_t *map, const uint32_t key, const uint32_t value) {
    if (map == nullptr) {
        return -1;
    }

    if (map->size * load_factor_numerator > map->capacity * load_factor_denominator) {
        if (!hashmap_resize(map, map->capacity * 2)) {
            return -2;
        }
    }

    const auto index = hash(key, map->capacity);
    auto node = map->buckets[index];

    while (node != nullptr) {
        if (node->key == key) {
            node->value = value;
            return 0;
        }
        node = node->next;
    }

    const auto new_node = (node_t *) malloc(sizeof(node_t));
    if (new_node == nullptr) {
        return -3;
    }

    new_node->key = key;
    new_node->value = value;
    new_node->next = map->buckets[index];

    map->buckets[index] = new_node;
    map->size++;

    return 0;
}

void hashmap_get(const hashmap_t *map, const uint32_t key, uint32_t *value) {
    if (map == nullptr || value == nullptr) {
        return;
    }

    const auto index = hash(key, map->capacity);
    auto node = map->buckets[index];

    while (node) {
        if (node->key == key) {
            *value = node->value;
            return;
        }
        node = node->next;
    }

    *value = 0;
}

void hashmap_free(hashmap_t *map) {
    if (map == nullptr) {
        return;
    }

    for (size_t i = 0; i < map->capacity; i++) {
        auto node = map->buckets[i];
        while (node != nullptr) {
            const auto next = node->next;
            free(node);
            node = next;
        }
    }

    free(map->buckets);
    free(map);
}

static void find(hashmap_iter_t *it) {
    const auto map = (hashmap_t *) it->map;
    while (it->index < map->capacity && map->buckets[it->index] == nullptr) {
        it->index++;
    }
    if (it->index < map->capacity) {
        it->node = map->buckets[it->index];
    }
}

static void forward(hashmap_iter_t *it) {
    it->node = it->node->next;
    if (it->node == nullptr) {
        it->index++;
        find(it);
    }
}


hashmap_iter_t *hashmap_iter_create(const hashmap_t *map) {
    if (map == nullptr) {
        return nullptr;
    }

    const auto it = (hashmap_iter_t *) malloc(sizeof(hashmap_iter_t));
    if (it == nullptr) {
        return nullptr;
    }

    it->map = map;
    it->index = 0;
    it->node = nullptr;

    find(it);
    return it;
}

bool hashmap_iter_next(hashmap_iter_t *it, uint32_t *key, uint32_t *value) {
    if (it == nullptr || it->node == nullptr) {
        return false;
    }

    *key = it->node->key;
    *value = it->node->value;

    forward(it);
    return true;
}

void hashmap_iter_free(hashmap_iter_t *it) {
    free(it);
}
