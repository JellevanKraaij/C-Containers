#include "vector.h"

#include <string.h>

bool vector_remove(t_vector *vector, size_t index)
{
	if (index >= vector->size)
		return (false);
	if (vector->destroy_fn)
		vector->destroy_fn(vector->data[index], vector->destroy_user_data);
	if (index < vector->size - 1)
		memmove(&vector->data[index], &vector->data[index + 1], (vector->size - index - 1) * sizeof(void *));
	vector->size--;
	return (true);
}
