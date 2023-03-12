#include "vector.h"

#include <stdlib.h>

void vector_destroy(t_vector *vector)
{
	if (vector == NULL)
		return;
	vector_clear(vector);
	free(vector->data);
	free(vector);
}

void vector_destroy_null(t_vector **vector)
{
	vector_destroy(*vector);
	*vector = NULL;
}
