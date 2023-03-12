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

t_vector *vector_shrink(t_vector **vector)
{
	void **new_data;

	if ((*vector)->length == (*vector)->capacity)
		return (*vector);
	new_data = realloc((*vector)->data, (*vector)->length * sizeof(void *));
	if (new_data == NULL)
		return (vector_destroy_null(vector), NULL);
	(*vector)->data = new_data;
	(*vector)->capacity = (*vector)->length;
	return (*vector);
}

t_vector *vector_resize(t_vector **vector, size_t length)
{
	size_t i;

	if (vector_reserve(vector, length) == NULL)
		return (NULL);
	if (length < (*vector)->length)
		return (vector_truncate(*vector, length), *vector);
	i = (*vector)->length;
	while (i < length)
	{
		(*vector)->data[i] = NULL;
		i++;
	}
	(*vector)->length = length;
	return (*vector);
}

void vector_truncate(t_vector *vector, size_t length)
{
	size_t i;

	if (length > vector->length)
		return ;

	if (vector->destroy_fn)
	{
		i = length;
		while (i < vector->length)
		{
			vector->destroy_fn(vector->data[i], vector->destroy_user_data);
			i++;
		}
	}
	vector->length = length;
}
