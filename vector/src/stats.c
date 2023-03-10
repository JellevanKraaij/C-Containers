#include "vector.h"

size_t vector_length(const t_vector *vector)
{
	return (vector->length);
}

size_t vector_capacity(const t_vector *vector)
{
	return (vector->capacity);
}
