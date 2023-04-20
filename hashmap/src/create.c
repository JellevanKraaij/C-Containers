#include "hashmap.h"
#include "hashmap-int.h"

#include <stdlib.h>

t_hashmap *hashmap_create(void)
{
	t_hashmap *hashmap = malloc(sizeof(t_hashmap));

	if (hashmap == NULL)
		return (NULL);
	hashmap->vector = vector_create();
	if (hashmap->vector == NULL)
		return (free(hashmap), NULL);
	vector_set_destroy_fn(hashmap->vector, _hashmap_destroy_hash_vector_fn, hashmap);
	hashmap->capacity = 0;
	hashmap->size = 0;
	hashmap->destroy_fn = NULL;
	hashmap->destroy_userdata = NULL;
	hashmap->key_cmp_fn = NULL;
	hashmap->key_cmp_userdata = NULL;
	hashmap->hash_fn = NULL;
	hashmap->hash_userdata = NULL;
	hashmap->load_factor = HASHMAP_DEFAULT_LOAD_FACTOR;

	if (hashmap_reserve(&hashmap, HASHMAP_DEFAULT_CAPACITY) == NULL)
		return (hashmap_destroy_null(&hashmap), NULL);
	hashmap->capacity = HASHMAP_DEFAULT_CAPACITY;
	return (hashmap);
}
