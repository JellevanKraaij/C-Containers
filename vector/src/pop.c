#include "vector.h"

#include <string.h>

bool vector_pop_back(t_vector *vector, void **data)
{
	return (vector_pop(vector, vector->size - 1, data));
}

bool vector_pop_front(t_vector *vector, void **data)
{
	return (vector_pop(vector, 0, data));
}

bool vector_pop(t_vector *vector, size_t index, void **data)
{
	if (index >= vector->size)
		return (false);
	if (data != NULL)
		*data = vector_get(vector, index);
	vector_remove(vector, index);
	return (true);
}
