#include "vector.h"

#include <stdlib.h>

t_vector *vector_create(void)
{
	t_vector *vector = malloc(sizeof(t_vector));

	if (vector == NULL)
		return NULL;
	vector->size = 0;
	vector->capacity = 0;
	vector->data = NULL;
	vector->destroy_fn = NULL;
	vector->destroy_user_data = NULL;
	vector->cmp_fn = NULL;
	vector->cmp_user_data = NULL;
	return (vector);
}
