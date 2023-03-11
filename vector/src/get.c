#include "vector.h"

void *vector_get(const t_vector *vector, size_t index)
{
	return (vector->data[index]);
}

bool vector_at(const t_vector *vector, size_t index, void **data)
{
	if (index >= vector->length)
		return (false);
	if (data)
		*data = vector_get(vector, index);
	return (true);
}
