#ifndef VECTOR_ALGO_H
#define VECTOR_ALGO_H

#include "vector.h"

/**
 * @brief Find an element in the vector
 * 
 * @param vector 
 * @param data pointer to the data to find
 * @param cmp_fn function to compare the data
 * @param index nullable pointer to store the index of the element
 * @return true if the element was found
 * @return false if the element was not found
 */
bool vector_find(t_vector *vector, void *data, size_t *index);

#endif
