#include "vector.h"

void vector_clear(t_vector *vector)
{
	size_t i;

	if (vector->destroy_fn)
	{
		i = 0;
		while (i < vector->length)
		{
			vector->destroy_fn(vector->data[i]);
			i++;
		}
	}
	vector->length = 0;
}

void vector_set_compare_f(t_vector *vector, t_vector_cmp_fn compare_fn)
{
	vector->cmp_fn = compare_fn;
}
