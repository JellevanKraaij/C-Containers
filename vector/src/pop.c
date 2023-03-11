#include "vector.h"

#include <string.h>

bool vector_pop_back(t_vector *vector, void **data)
{
	if (vector->length == 0)
		return (false);
	if (data != NULL)
		*data = vector_get(vector, vector->length - 1);
	else if (vector->destroy_f)
		vector->destroy_f(vector->data[vector->length - 1]);
	vector->length--;
	return (true);
}

bool vector_pop_front(t_vector *vector, void **data)
{
	if (vector->length == 0)
		return (false);
	if (data != NULL)
		*data = vector_get(vector, 0);
	else if (vector->destroy_f)
		vector->destroy_f(vector->data[0]);
	memmove(&vector->data[0], &vector->data[1], (vector->length - 1) * sizeof(void *));
	vector->length--;
	return (true);
}
