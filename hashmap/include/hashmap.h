#ifndef	HASHMAP_H
#define	HASHMAP_H

#if defined(__cplusplus) &&  !defined(C_CONTAINER_OVERRIDE_CXX)
#warning "Just use the c++ std::unordered_map bruh"
#endif

#include <vector.h>

#include <stddef.h>

typedef void (*t_hashmap_destroy_fn)(void *key, void *value, void *user_data);
typedef void (*t_hashmap_key_cmp_fn)(void *a, void *b, void *user_data);
typedef void (*t_hashmap_hash_fn)(void *key, void *user_data);

typedef struct {
	void *key;
	void *value;
} t_hashmap_pair;

typedef struct s_hashmap {
	size_t size;
	size_t capacity;
	t_vector *vector;
	t_hashmap_destroy_fn destroy_fn;
	void *destroy_userdata;
	t_hashmap_key_cmp_fn key_cmp_fn;
	void *key_cmp_userdata;
	t_hashmap_hash_fn hash_fn;
	void *hash_userdata;
} t_hashmap;

t_hashmap *hashmap_create(void);

void hashmap_destroy(t_hashmap *hashmap);
void hashmap_destroy_null(t_hashmap **hashmap);

t_hashmap *hashmap_reserve(t_hashmap **hashmap, size_t capacity);
t_hashmap *hashmap_shrink(t_hashmap **hashmap);
t_hashmap *hashmap_clear(t_hashmap *hashmap);

void hashmap_set_destroy_fn(t_hashmap *hashmap, t_hashmap_destroy_fn fn, void *user_data);
void hashmap_set_key_cmp_fn(t_hashmap *hashmap, t_hashmap_key_cmp_fn fn, void *user_data);
void hashmap_set_hash_fn(t_hashmap *hashmap, t_hashmap_hash_fn fn, void *user_data);

t_hashmap *hashmap_push(t_hashmap **hashmap, void *key, void *value);
bool hashmap_pop(t_hashmap *hashmap, void *key, void **value);

void *hashmap_get(t_hashmap *hashmap, void *key);
bool hasmap_at(t_hashmap *hashmap, void *key, void **value);

t_hashmap *hashmap_set(t_hashmap **hashmap, void *key, void *value);

void hashmap_remove(t_hashmap *hashmap, void *key);

bool hashmap_has_key(t_hashmap *hashmap, void *key);

size_t hashmap_size(t_hashmap *hashmap);
size_t hashmap_capacity(t_hashmap *hashmap);

#endif
