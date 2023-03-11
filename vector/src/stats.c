#include "vector.h"

size_t vector_length(const t_vector *vector)
{
	return (vector->length);
}

size_t vector_capacity(const t_vector *vector)
{
	return (vector->capacity);
}

bool vector_valid_index(const t_vector *vector, size_t index)
{
	return (index < vector->length);
}
