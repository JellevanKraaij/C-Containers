#ifndef HASHMAP_INT_H
#define HASHMAP_INT_H

#include "hashmap.h"

size_t _hashmap_hash(const t_hashmap *hashmap, const void *key);

t_vector *_hashmap_create_bucket(t_hashmap *hashmap);

t_hashmap *_hashmap_bucket_add_pair(t_hashmap **hashmap, size_t index, t_hashmap_pair *pair);

void _hashmap_destroy_bucket_fn(void *pair_p, void *user_data);
void _hashmap_destroy_hash_vector_fn(void *bucket_p, void *user_data);

#endif
