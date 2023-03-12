#include "vector.h"

#include <stdlib.h>

void vector_destroy(t_vector *vector)
{
	size_t i;

	if (vector == NULL)
		return;
	if (vector->destroy_fn != NULL)
	{
		i = 0;
		while (i < vector->length)
		{
			vector->destroy_fn(vector->data[i]);
			i++;
		}
	}
	free(vector->data);
	free(vector);
}

void vector_destroy_null(t_vector **vector)
{
	vector_destroy(*vector);
	*vector = NULL;
}
