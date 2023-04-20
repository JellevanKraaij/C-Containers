#include "hashmap-int.h"

#include <stdlib.h>

// This function is called by vector_destroy() for each element in a bucket. It frees the pair and calls the destroy function if it exists.
void _hashmap_destroy_bucket_fn(void *pair_p, void *user_data)
{
	t_hashmap *hashmap = user_data;
	t_hashmap_pair *pair = pair_p;

	if (pair == NULL)
		return;
	if (hashmap->destroy_fn)
		hashmap->destroy_fn(pair->key, pair->value, hashmap->destroy_userdata);
	free(pair);
}

// This function is called by vector_destroy() for each element in the vector. It frees the bucket.
void _hashmap_destroy_hash_vector_fn(void *bucket_p, void *user_data)
{
	(void)user_data;
	t_vector *bucket = bucket_p;
	if (bucket == NULL)
		return;
	vector_destroy(bucket);
}

t_vector *_hashmap_create_bucket(t_hashmap *hashmap)
{
	t_vector *bucket = vector_create();
	if (bucket == NULL)
		return (NULL);
	vector_set_destroy_fn(bucket, _hashmap_destroy_bucket_fn, hashmap);
	return (bucket);
}

t_hashmap *_hashmap_bucket_add_pair(t_hashmap **hashmap, size_t index, t_hashmap_pair *pair)
{
	t_vector **bucket = (t_vector **)vector_get_addr((*hashmap)->vector, index);

	if (*bucket == NULL)
	{
		*bucket = _hashmap_create_bucket(*hashmap);
		if (*bucket == NULL)
			return (hashmap_destroy_null(hashmap), NULL);
	}
	if (vector_push_back(bucket, pair) == NULL)
		return (hashmap_destroy_null(hashmap), NULL);
	(*hashmap)->size++;
	return (*hashmap);
}

size_t _hashmap_hash(const t_hashmap *hashmap, const void *key)
{
	if (hashmap->hash_fn)
		return (hashmap->hash_fn(key, hashmap->hash_userdata));
	return ((size_t)key % vector_size(hashmap->vector));
}
