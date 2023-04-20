#ifndef VECTOR_H
#define VECTOR_H

#if defined(__cplusplus) &&  !defined(C_CONTAINER_OVERRIDE_CXX)
#warning "Just use the c++ std::vector bruh"
#endif

#include <stddef.h>
#include <stdbool.h>

typedef int (*t_vector_cmp_fn)(const void *a, const void *b, void *user_data);
typedef void (*t_vector_destroy_fn)(void *data, void *user_data);

typedef struct t_vector {
	void **data;
	size_t size;
	size_t capacity;
	t_vector_destroy_fn destroy_fn;
	void *destroy_user_data;
	t_vector_cmp_fn cmp_fn;
	void *cmp_user_data;
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
 * @param destroy_fn function pointer
 * @param user_data user data to pass to the destroy function
 */
void vector_set_destroy_fn(t_vector *vector, t_vector_destroy_fn destroy_fn, void *user_data);

/**
 * @brief Set the compare function
 * 
 * @details The compare function will be called when an element is searched / sorted
 * @details The compare function should return 0 if a == b, < 0 if a < b and > 0 if a > b
 * 
 * @param vector 
 * @param cmp_fn function pointer
 * @param user_data user data to pass to the compare function
 */
void vector_set_compare_fn(t_vector *vector, t_vector_cmp_fn compare_fn, void *user_data);

// ---[ Stats functions ]-------------------------------------------------------------------------

/**
 * @brief Get size of the vector (number of elements)
 * @details Will return 0 if vector is NULL
 * 
 * @param vector (null pointer is allowed)
 * @return vector size
 */
size_t vector_size(const t_vector *vector);

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
 * @attention If the index is equal or greater than the size, the element will be added to the end
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

/**
 * @brief Get the address of the element at index
 * @attention No bounds checking is done
 * 
 * @param vector 
 * @param index 
 * @return pointer to the data
 */
void **vector_get_addr(const t_vector *vector, size_t index);

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
 * @brief Truncate the vector to size
 * 
 * @attention Removed elements are destroyed
 * @attention If the size is greater than the current size, nothing happens
 * 
 * @param vector 
 * @param size 
 * @return true if the vector was truncated
 * @return false if the size is greater than the current size
 */
void vector_truncate(t_vector *vector, size_t size);

/**
 * @brief Resize the vector to size
 * 
 * @attention If the size is greater than the current size, the vector will be extended with NULL elements
 * @attention If the size is smaller than the current size, the vector will be truncated
 * @attention Removed elements are destroyed
 * 
 * @param vector 
 * @param size 
 */
t_vector *vector_resize(t_vector **vector, size_t size);

#endif
