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

	if ((*vector)->size == (*vector)->capacity)
		return (*vector);
	new_data = realloc((*vector)->data, (*vector)->size * sizeof(void *));
	if (new_data == NULL)
		return (vector_destroy_null(vector), NULL);
	(*vector)->data = new_data;
	(*vector)->capacity = (*vector)->size;
	return (*vector);
}

t_vector *vector_resize(t_vector **vector, size_t size)
{
	size_t i;

	if (vector_reserve(vector, size) == NULL)
		return (NULL);
	if (size < (*vector)->size)
		return (vector_truncate(*vector, size), *vector);
	i = (*vector)->size;
	while (i < size)
	{
		(*vector)->data[i] = NULL;
		i++;
	}
	(*vector)->size = size;
	return (*vector);
}

void vector_truncate(t_vector *vector, size_t size)
{
	size_t i;

	if (size > vector->size)
		return ;

	if (vector->destroy_fn)
	{
		i = size;
		while (i < vector->size)
		{
			vector->destroy_fn(vector->data[i], vector->destroy_user_data);
			i++;
		}
	}
	vector->size = size;
}
