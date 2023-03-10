#include "vector.h"

void *vector_get(const t_vector *vector, size_t index)
{
	return (vector->data[index]);
}

const t_vector *vector_at(const t_vector *vector, size_t index, void **data)
{
	if (index >= vector->length)
		return (NULL);
	*data = vector_get(vector, index);
	return (vector);
}
