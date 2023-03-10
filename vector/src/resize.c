#include "vector.h"

#include <stdlib.h>

t_vector *vector_reserve(t_vector **vector, size_t capacity)
{
	void **new_data;

	if (capacity <= (*vector)->capacity)
		return (*vector);
	new_data = realloc((*vector)->data, capacity * sizeof(void *));
	if (new_data == NULL)
		return (vector_destroy_null(vector), NULL);
	(*vector)->data = new_data;
	(*vector)->capacity = capacity;
	return (*vector);
}
