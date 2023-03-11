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
	t_vector_destroy_f destroy_f;
} t_vector;

// ---[ Create & Destroy & Memory functions ]--------------------------------------------------------------

/**
 * @brief Create a new vector
 * 
 * @return pointer to the vector
 * @return NULL if an error occured
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

/**
 * @brief Clear the vector
 * 
 * @param vector 
 */
void vector_clear(t_vector *vector);

/**
 * 
 * @brief Reserve memory atleast for capacity elements
 * 
 * @details If the capacite is smaller than or equal to the current capacity, nothing happens
 * @attention If this function fails, the vector is destroyed
 * 
 * @param vector 
 * @param capacity 
 * @return pointer to the vector
 * @return NULL if an error occured
 */
t_vector *vector_reserve(t_vector **vector, size_t capacity);

/**
 * @brief Shrink the vector to the minimum capacity
 * 
 * @attention If this function fails, the vector is destroyed
 * 
 * @param vector 
 * @return pointer to the vector
 * @return NULL if an error occured
 */
t_vector *vector_shrink(t_vector **vector);

/**
 * @brief Set the destroy function
 * 
 * @details The destroy function will be called when an element is overwritten or removed
 * 
 * @param vector 
 * @param destroy function pointer
 */

void vector_set_destroy_f(t_vector *vector, t_vector_destroy_f destroy_f);


// ---[ Stats functions ]-------------------------------------------------------------------------

/**
 * @brief Get length of the vector
 * 
 * @param vector 
 * @return vector length
 */
size_t vector_length(const t_vector *vector);

/**
 * @brief Get capacity of the vector
 * 
 * @param vector 
 * @return vector capacity
 */
size_t vector_capacity(const t_vector *vector);

/**
 * @brief Checks if index is valid
 * 
 * @param vector 
 * @param index 
 * @return true if index is valid
 * @return false if index is invalid
 */
bool vector_valid_index(const t_vector *vector, size_t index);

// ---[ Add functions ]---------------------------------------------------------------------------

/**
 * @brief Add an element to the end of the vector
 * 
 * @attention If this function fails, the vector is destroyed
 * 
 * @param vector 
 * @param data 
 * @return pointer to the vector
 * @return NULL if an error occured
 */
t_vector *vector_push_back(t_vector **vector, void *data);

/**
 * @brief Add an element to the front of the vector
 * 
 * @attention If this function fails, the vector is destroyed
 * 
 * @param vector 
 * @param data 
 * @return pointer to the vector
 * @return NULL if an error occured
 */
t_vector *vector_push_front(t_vector **vector, void *data);

/**
 * @brief Insert an element at index
 * 
 * @attention If this function fails, the vector is destroyed
 * @attention If the index is equal or greater than the length, the element will be added to the end
 * 
 * @param vector 
 * @param index 
 * @param data 
 * @return pointer to the vector
 * @return NULL if an error occured
 */
t_vector *vector_insert(t_vector **vector, size_t index, void *data);


// ---[ Remove functions ]------------------------------------------------------------------------

/**
 * @brief Remove the last element of the vector
 * 
 * @attention If the data pointer is NULL, the element will be destroyed
 * 
 * @param vector 
 * @param data nullable pointer to the popped data
 * @return pointer to the vector
 * @return true if the vector is not empty
 * @return false if the vector is empty
 */
bool vector_pop_back(t_vector *vector, void **data);

/**
 * @brief Remove the first element of the vector
 * 
 * @attention If the data pointer is NULL, the element will be destroyed
 * 
 * @param vector 
 * @param data nullable pointer will be set to the data
 * @return true if the vector is not empty
 * @return false if the vector is empty
 */
bool vector_pop_front(t_vector *vector, void **data);

/**
 * @brief Remove the element at index
 * 
 * @attention If the data pointer is NULL, the element will be destroyed
 * 
 * @param vector 
 * @param index 
 * @param data nullable pointer will be set to the data
 * @return true if the index is valid
 * @return false if the index is invalid
 */
bool vector_pop(t_vector *vector, size_t index, void **data);

/**
 * @brief Remove the element at index
 * 
 * @attention The element at index will be destroyed
 * 
 * @param vector 
 * @param index 
 * @return true if the index is valid
 * @return false if the index is invalid
 */
bool vector_remove(t_vector *vector, size_t index);

// ---[ Get functions ]---------------------------------------------------------------------------

/**
 * @brief Get the element at index
 * @attention No bounds checking is done
 * 
 * @param vector 
 * @param index 
 * @return pointer to the data
 */
void *vector_get(const t_vector *vector, size_t index);

/**
 * @brief Get the element at index
 * 
 * @param vector 
 * @param index 
 * @param data nullable pointer will be set to the data
 * @return true if the index is valid
 * @return false if the index is invalid
 */
bool vector_at(const t_vector *vector, size_t index, void **data);

// ---[ Set functions ]---------------------------------------------------------------------------

/**
 * @brief Set the element at index
 * 
 * @attention The element at index will be destroyed
 * 
 * @param vector 
 * @param index 
 * @param data 
 * @return true if the index is valid
 * @return false if the index is invalid
 */
bool vector_set(t_vector *vector, size_t index, void *data);

// ---[ Modify functions ]------------------------------------------------------------------------

/**
 * @brief Truncate the vector to length
 * 
 * @attention Removed elements are destroyed
 * @attention If the length is greater than the current length, nothing happens
 * 
 * @param vector 
 * @param length 
 * @return true if the vector was truncated
 * @return false if the length is greater than the current length
 */
void vector_truncate(t_vector *vector, size_t length);

#endif
