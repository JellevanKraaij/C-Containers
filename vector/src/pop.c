#include "vector.h"

#include <string.h>

t_vector *vector_pop_back(t_vector **vector, void **data)
{
	if ((*vector)->length == 0)
		return (NULL);
	if (data != NULL)
		*data = vector_get(*vector, (*vector)->length - 1);
	(*vector)->length--;
	return (*vector);
}

t_vector *vector_pop_front(t_vector **vector, void **data)
{
	if ((*vector)->length == 0)
		return (NULL);
	if (data != NULL)
		*data = vector_get(*vector, 0);
	memmove(&(*vector)->data[0], &(*vector)->data[1], ((*vector)->length - 1) * sizeof(void *));
	(*vector)->length--;
	return (*vector);
}
