#include "vector.h"

size_t vector_size(const t_vector *vector)
{
	if (vector == NULL)
		return (0);
	return (vector->size);
}

size_t vector_capacity(const t_vector *vector)
{
	return (vector->capacity);
}

bool vector_valid_index(const t_vector *vector, size_t index)
{
	return (index < vector->size);
}
