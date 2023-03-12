#include "hashmap.h"

#include <stdlib.h>

void hashmap_destoy_null(t_hashmap **hashmap)
{
	hashmap_destroy(*hashmap);
	*hashmap = NULL;
}

void hashmap_destroy(t_hashmap *hashmap)
{
	vector_destroy(hashmap->vector);
	free(hashmap);
}
