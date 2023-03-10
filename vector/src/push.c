#include "vector.h"

#include <string.h>

t_vector *vector_push_back(t_vector **vector, void *data)
{
	if (vector_reserve(vector, (*vector)->length + 1) == NULL)
		return (NULL);
	(*vector)->data[(*vector)->length] = data;
	(*vector)->length++;
	return (*vector);
}

t_vector *vector_push_front(t_vector **vector, void *data)
{
	size_t i;

	if (vector_reserve(vector, (*vector)->length + 1) == NULL)
		return (NULL);
	i = (*vector)->length;
	memmove(&(*vector)->data[1], &(*vector)->data[0], i * sizeof(void *));
	(*vector)->data[0] = data;
	(*vector)->length++;
	return (*vector);
}
