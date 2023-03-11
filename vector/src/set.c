#include "vector.h"

bool vector_set(t_vector *vector, size_t index, void *data)
{
	if (!vector_valid_index(vector, index))
		return (false);
	if (vector->destroy)
		vector->destroy(vector->data[index]);
	vector->data[index] = data;
	return (true);
}
