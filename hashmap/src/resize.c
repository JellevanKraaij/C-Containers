#include "hashmap.h"
#include "hashmap-int.h"

#include <stdlib.h>

static size_t next_power_of_two(size_t n)
{
	size_t i = 1;

	while (i < n)
		i <<= 1;
	return (i);
}

#include <stdio.h>


static t_hashmap *hashmap_rehash(t_hashmap **hashmap, const t_vector *old_vector)
{
	size_t old_vec_size = vector_size(old_vector);
	size_t new_vec_size = vector_size((*hashmap)->vector);

	size_t i = 0;
	while (i < old_vec_size)
	{
		t_vector *bucket = vector_get(old_vector, i);

		size_t j = 0;
		while (j < vector_size(bucket))
		{
			t_hashmap_pair *pair = vector_get(bucket, j);
			size_t index = _hashmap_hash(*hashmap, pair->key) % new_vec_size;
			if (_hashmap_bucket_add_pair(hashmap, index, pair) == NULL)
				return (hashmap_destroy_null(hashmap), NULL);
			j++;
		}
		vector_set_destroy_fn(bucket, NULL, NULL);
		vector_destroy(bucket);
		vector_set(bucket, i, NULL);
		i++;
	}
	return (*hashmap);
}

//TODO: add tests
t_hashmap *hashmap_reserve(t_hashmap **hashmap, size_t capacity)
{
	if (capacity <= (*hashmap)->capacity)
		return (*hashmap);
	
	size_t vec_size = (float)capacity / (*hashmap)->load_factor;
	vec_size = next_power_of_two(vec_size);

	printf("vec_size: %zu\n", vec_size);

	t_vector *old_vector = (*hashmap)->vector;
	t_vector *new_vector = vector_create();
	if (new_vector == NULL)
		return (hashmap_destroy_null(hashmap), NULL);
	vector_set_destroy_fn(new_vector, _hashmap_destroy_hash_vector_fn, *hashmap);
	(*hashmap)->vector = new_vector;
	if (vector_resize(&(*hashmap)->vector, vec_size) == NULL)
		return (hashmap_destroy_null(hashmap), NULL);
	if (hashmap_rehash(hashmap, old_vector) == NULL)
		return (hashmap_destroy_null(hashmap), vector_destroy(old_vector), NULL);
	vector_destroy(old_vector);
	(*hashmap)->capacity = (float)vec_size * (*hashmap)->load_factor;
	return (*hashmap);
}

