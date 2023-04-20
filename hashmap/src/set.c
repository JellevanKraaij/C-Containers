#include "hashmap.h"

//TODO: add tests for this function
void hashmap_set_destroy_fn(t_hashmap *hashmap, t_hashmap_destroy_fn destroy_fn, void *user_data)
{
	hashmap->destroy_fn = destroy_fn;
	hashmap->destroy_userdata = user_data;
}

void hashmap_set_key_cmp_fn(t_hashmap *hashmap, t_hashmap_key_cmp_fn key_cmp_fn, void *user_data)
{
	hashmap->key_cmp_fn = key_cmp_fn;
	hashmap->key_cmp_userdata = user_data;
}

void hashmap_set_hash_fn(t_hashmap *hashmap, t_hashmap_hash_fn hash_fn, void *user_data)
{
	hashmap->hash_fn = hash_fn;
	hashmap->hash_userdata = user_data;
}
