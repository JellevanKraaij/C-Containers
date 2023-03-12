#include "vector.h"
#include "vector-algo.h"

static bool vector_data_eq(t_vector_cmp_fn cmp_f, void *a,void *b)
{
	if (cmp_f == NULL)
		return (a == b);
	return (cmp_f(a, b) == 0);
}

bool vector_find(t_vector *vector, void *data, size_t *index)
{
	size_t i;

	i = 0;
	while (i < vector->length)
	{
		if (vector_data_eq(vector->cmp_fn, vector->data[i], data))
		{
			if (index)
				*index = i;
			return (true);
		}
		i++;
	}
	return (false);
}
