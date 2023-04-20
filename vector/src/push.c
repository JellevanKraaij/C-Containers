#include "vector.h"

#include <string.h>

t_vector *vector_push_back(t_vector **vector, void *data)
{
	return (vector_insert(vector, (*vector)->size, data));
}

t_vector *vector_push_front(t_vector **vector, void *data)
{
	return (vector_insert(vector, 0, data));
}
