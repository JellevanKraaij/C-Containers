#ifndef VECTOR_H
#define VECTOR_H

#if defined(__cplusplus) &&  !defined(VECTOR_OVERRIDE_CXX)
#warning "Just use the c++ std::vector bruh"
#endif

#include <stddef.h>
#include <stdbool.h>

typedef void (*t_vector_destroy_f)(void *);

typedef struct t_vector {
	void **data;
	size_t length;
	size_t capacity;
	t_vector_destroy_f destroy;
} t_vector;

// ---[ Create & Destroy functions ]--------------------------------------------------------------
/**
 * @brief Create a new vector
 * 
 * @return t_vector* pointer to the vector or NULL if an error occured
 */
t_vector *vector_create(void);

/**
 * @brief Destroy the vector
 * 
 * @param vector 
 */
void vector_destroy(t_vector *vector);

/**
 * @brief Destroy the vector and set the pointer to NULL
 * 
 * @param vector 
 */
void vector_destroy_null(t_vector **vector);

// ---[ Stats functions ]-------------------------------------------------------------------------

/**
 * 
 * @brief Reserve memory atleast for capacity elements
 * 
 * @details If the capacite is smaller than or equal to the current capacity, nothing happens
 * 
 * @param vector 
 * @param capacity 
 * @return t_vector* pointer to the vector or NULL if an error occured
 */
t_vector *vector_reserve(t_vector **vector, size_t capacity);

/**
 * @brief Get length of the vector
 * 
 * @param vector 
 * @return size_t vector length
 */
size_t vector_length(const t_vector *vector);

/**
 * @brief Get capacity of the vector
 * 
 * @param vector 
 * @return size_t vector capacity
 */
size_t vector_capacity(const t_vector *vector);

// ---[ Push & Pop functions ]--------------------------------------------------------------------

/**
 * @brief Add an element to the end of the vector
 * 
 * @param vector 
 * @param data 
 * @return t_vector* pointer to the vector or NULL if an error occured
 */
t_vector *vector_push_back(t_vector **vector, void *data);

/**
 * @brief Add an element to the front of the vector
 * 
 * @param vector 
 * @param data 
 * @return t_vector* pointer to the vector or NULL if an error occured
 */
t_vector *vector_push_front(t_vector **vector, void *data);

/**
 * @brief Remove the last element of the vector
 * 
 * @param vector 
 * @param data nullable pointer to the popped data
 * @return t_vector*  pointer to the vector or NULL if an error occured
 */
t_vector *vector_pop_back(t_vector **vector, void **data);

/**
 * @brief Remove the first element of the vector
 * 
 * @param vector 
 * @param data nullable pointer to the popped data
 * @return t_vector* pointer to the vector or NULL if an error occured
 */
t_vector *vector_pop_front(t_vector **vector, void **data);

// ---[ Get functions ]---------------------------------------------------------------------------

/**
 * @brief Get the element at index
 * @attention No bounds checking is done
 * 
 * @param vector 
 * @param index 
 * @return void* pointer to the data
 */
void *vector_get(const t_vector *vector, size_t index);

/**
 * @brief Get the element at index
 * 
 * @param vector 
 * @param index 
 * @param data pointer to the data
 * @return const t_vector* pointer to the vector or NULL if an error occured
 */
const t_vector *vector_at(const t_vector *vector, size_t index, void **data);


#endif
