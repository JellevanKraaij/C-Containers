#include "vector.h"

#include <stdlib.h>

void vector_destroy(t_vector *vector)
{
	size_t i;

	if (vector == NULL)
		return;
	if (vector->destroy_f != NULL)
	{
		i = 0;
		while (i < vector->length)
		{
			vector->destroy_f(vector->data[i]);
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

void vector_set_destroy_f(t_vector *vector, t_vector_destroy_f destroy_f)
{
	vector->destroy_f = destroy_f;
}
