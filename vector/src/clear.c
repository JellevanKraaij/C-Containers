#include "vector.h"

void vector_clear(t_vector *vector)
{
	size_t i;

	if (vector->destroy)
	{
		i = 0;
		while (i < vector->length)
		{
			vector->destroy(vector->data[i]);
			i++;
		}
	}
	vector->length = 0;
}
