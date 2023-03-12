#include "vector.h"

bool vector_set(t_vector *vector, size_t index, void *data)
{
	if (!vector_valid_index(vector, index))
		return (false);
	if (vector->destroy_fn)
		vector->destroy_fn(vector->data[index]);
	vector->data[index] = data;
	return (true);
}

void vector_set_destroy_fn(t_vector *vector, t_vector_destroy_fn destroy_fn)
{
	vector->destroy_fn = destroy_fn;
}

void vector_set_compare_fn(t_vector *vector, t_vector_cmp_fn compare_fn)
{
	vector->cmp_fn = compare_fn;
}
