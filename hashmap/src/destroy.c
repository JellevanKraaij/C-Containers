#include "hashmap.h"

#include <stdlib.h>

void hashmap_destroy(t_hashmap *hashmap)
{
	if (hashmap == NULL)
		return;
	vector_destroy(hashmap->vector);
	free(hashmap);
}

void hashmap_destroy_null(t_hashmap **hashmap)
{
	if (*hashmap == NULL)
		return;
	hashmap_destroy(*hashmap);
	*hashmap = NULL;
}
