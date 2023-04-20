#include <vector.h>

#include <string.h>

t_vector *vector_insert(t_vector **vector, size_t index, void *data)
{
	if (index > (*vector)->size)
		index = (*vector)->size;
	if (vector_reserve(vector, (*vector)->size + 1) == NULL)
		return (NULL);
	if (index < (*vector)->size)
		memmove(&(*vector)->data[index + 1], &(*vector)->data[index], ((*vector)->size - index) * sizeof(void *));
	(*vector)->data[index] = data;
	(*vector)->size++;
	return (*vector);
}
