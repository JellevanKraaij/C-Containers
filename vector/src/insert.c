#include <vector.h>

#include <string.h>

t_vector *vector_insert(t_vector **vector, size_t index, void *data)
{
	if (index > (*vector)->length)
		index = (*vector)->length;
	if (vector_reserve(vector, (*vector)->length + 1) == NULL)
		return (NULL);
	if (index < (*vector)->length)
		memmove(&(*vector)->data[index + 1], &(*vector)->data[index], ((*vector)->length - index) * sizeof(void *));
	(*vector)->data[index] = data;
	(*vector)->length++;
	return (*vector);
}
