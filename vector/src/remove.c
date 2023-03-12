#include "vector.h"

#include <string.h>

bool vector_remove(t_vector *vector, size_t index)
{
	if (index >= vector->length)
		return (false);
	if (vector->destroy_fn)
		vector->destroy_fn(vector->data[index], vector->destroy_user_data);
	if (index < vector->length - 1)
		memmove(&vector->data[index], &vector->data[index + 1], (vector->length - index - 1) * sizeof(void *));
	vector->length--;
	return (true);
}
