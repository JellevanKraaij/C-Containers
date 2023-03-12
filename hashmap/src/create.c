#include "hashmap.h"

#include <stdlib.h>

void hashmap_destroy_vector_fn(void *pair, void *user_data)
{
	t_hashmap *hashmap = user_data;

	if (pair == NULL)
		return;

	if (hashmap->destroy_fn != NULL)
		hashmap->destroy_fn(((t_hashmap_pair *)pair)->key, ((t_hashmap_pair *)pair)->value, hashmap->destroy_userdata);

	free(pair);
}

t_hashmap *hashmap_create(void)
{
	t_hashmap *hashmap = malloc(sizeof(t_hashmap));

	if (hashmap == NULL)
		return (NULL);
	hashmap->size = 0;
	hashmap->capacity = 0;
	hashmap->vector = vector_create();
	if (hashmap->vector == NULL)
		return (free(hashmap), NULL);
	vector_set_destroy_fn(hashmap->vector, hashmap_destroy_vector_fn, hashmap);
	hashmap->destroy_fn = NULL;
	hashmap->destroy_userdata = NULL;
	hashmap->key_cmp_fn = NULL;
	hashmap->key_cmp_userdata = NULL;
	hashmap->hash_fn = NULL;
	hashmap->hash_userdata = NULL;
	return (hashmap);
}
