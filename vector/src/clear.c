#include "vector.h"

void vector_clear(t_vector *vector)
{
	size_t i;

	if (vector->destroy_fn)
	{
		i = 0;
		while (i < vector->length)
		{
			vector->destroy_fn(vector->data[i], vector->destroy_user_data);
			i++;
		}
	}
	vector->length = 0;
}

