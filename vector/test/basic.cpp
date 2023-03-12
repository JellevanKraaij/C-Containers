extern "C" {
	#define VECTOR_OVERRIDE_CXX
	#include <vector.h>
}

#include <gtest/gtest.h>
#include "BasicFixture.hpp"

TEST(Basic, CreateAndDestroy) {
	t_vector *vector = vector_create();
	ASSERT_NE(nullptr, vector);
	vector_destroy(vector);
}

TEST_F(BasicF, Reserve) {
	vector_reserve(&vector, 10);
	ASSERT_GE(vector_capacity(vector), 10);	
}

TEST_F(BasicF, Length) {
	ASSERT_EQ(0, vector_length(vector));
	vector_push_back(&vector, (void *)42);
	ASSERT_EQ(1, vector_length(vector));
	vector_push_back(&vector, (void *)43);
	ASSERT_EQ(2, vector_length(vector));
}

TEST_F(BasicF, Capacity) {
	ASSERT_GE(0, vector_capacity(vector));
	vector_push_back(&vector, (void *)42);
	ASSERT_GE(1, vector_capacity(vector));
	vector_push_back(&vector, (void *)43);
	ASSERT_GE(2, vector_capacity(vector));
}

TEST_F(BasicF, Shrink)
{
	vector_reserve(&vector, 10);
	ASSERT_GE(vector_capacity(vector), 10);

	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)43);

	vector_shrink(&vector);

	ASSERT_GE(2, vector_capacity(vector));
}

TEST_F(BasicF, PushBack) {
	ASSERT_NE(nullptr, vector_push_back(&vector, (void *)42));
	ASSERT_NE(nullptr, vector_push_back(&vector, (void *)43));
	ASSERT_EQ(2, vector_length(vector));
	EXPECT_EQ((void *)42, vector_get(vector, 0));
	EXPECT_EQ((void *)43, vector_get(vector, 1));
}

TEST_F(BasicF, PushFront)
{
	ASSERT_TRUE(vector_push_front(&vector, (void *)42));
	ASSERT_TRUE(vector_push_front(&vector, (void *)43));
	ASSERT_EQ(2, vector_length(vector));
	EXPECT_EQ((void *)43, vector_get(vector, 0));
	EXPECT_EQ((void *)42, vector_get(vector, 1));
}

TEST_F(BasicF, Pop)
{
	ASSERT_FALSE(vector_pop(vector, 0, nullptr));

	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)43);
	vector_push_back(&vector, (void *)44);
	ASSERT_TRUE(vector_pop(vector, 1, nullptr));
	EXPECT_EQ(2, vector_length(vector));

	void *data = nullptr;
	ASSERT_TRUE(vector_pop(vector, 0, &data));
	ASSERT_EQ(1, vector_length(vector));
	EXPECT_EQ((void *)42, data);
}

TEST_F(BasicF, PopBack) {

	ASSERT_FALSE(vector_pop_back(vector, nullptr));

	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)43);
	ASSERT_TRUE(vector_pop_back(vector, nullptr));
	EXPECT_EQ(1, vector_length(vector));

	void *data = nullptr;
	ASSERT_TRUE(vector_pop_back(vector, &data));
	ASSERT_EQ(0, vector_length(vector));
	EXPECT_EQ((void *)42, data);
}

TEST_F(BasicF, PopFront)
{
	ASSERT_FALSE(vector_pop_front(vector, nullptr));

	vector_push_front(&vector, (void *)42);
	vector_push_front(&vector, (void *)43);
	ASSERT_TRUE(vector_pop_front(vector, nullptr));
	EXPECT_EQ(1, vector_length(vector));

	void *data = nullptr;
	ASSERT_TRUE(vector_pop_front(vector, &data));
	ASSERT_EQ(0, vector_length(vector));
	EXPECT_EQ((void *)42, data);
}


TEST_F(BasicF, Get)
{
	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)43);
	EXPECT_EQ((void *)42, vector_get(vector, 0));
	EXPECT_EQ((void *)43, vector_get(vector, 1));
}

TEST_F(BasicF, At)
{
	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)43);

	void *data = nullptr;
	ASSERT_TRUE(vector_at(vector, 0, &data));
	EXPECT_EQ((void *)42, data);
	ASSERT_TRUE(vector_at(vector, 1, &data));
	EXPECT_EQ((void *)43, data);
}

TEST_F(BasicF, AtFail)
{
	EXPECT_FALSE(vector_at(vector, 0, nullptr));

	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)43);

	void *data = nullptr;
	EXPECT_FALSE(vector_at(vector, 2, &data));
	EXPECT_FALSE(vector_at(vector, 3, &data));
	EXPECT_EQ(nullptr, data);
}

TEST_F(BasicF, Set)
{
	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)43);
	EXPECT_EQ((void *)42, vector_get(vector, 0));
	EXPECT_EQ((void *)43, vector_get(vector, 1));

	vector_set(vector, 0, (void *)44);
	vector_set(vector, 1, (void *)45);
	EXPECT_EQ((void *)44, vector_get(vector, 0));
	EXPECT_EQ((void *)45, vector_get(vector, 1));
}

TEST_F(BasicF, SetFail)
{
	EXPECT_FALSE(vector_set(vector, 0, (void *)42));
	EXPECT_FALSE(vector_set(vector, 1, (void *)42));

	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)43);
	EXPECT_FALSE(vector_set(vector, 2, (void *)42));
	EXPECT_FALSE(vector_set(vector, 3, (void *)42));
}

TEST_F(BasicF, Clear)
{
	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)43);
	ASSERT_EQ(2, vector_length(vector));
	vector_clear(vector);
	ASSERT_EQ(0, vector_length(vector));
}

static int destroy_f_called = 0;
void destroy_fn(void *data)
{
	(void)data;
	destroy_f_called++;
}

TEST_F(BasicF, DestroyFunction)
{
	// Test indivual functions that destroy data
	destroy_f_called = 0;
	vector_set_destroy_fn(vector, destroy_fn);

	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)43);
	vector_push_back(&vector, (void *)44);

	vector_pop_back(vector, nullptr);
	vector_set(vector, 0, (void *)45);
	vector_pop_front(vector, nullptr);
	vector_remove(vector, 0);
	
	EXPECT_EQ(4, destroy_f_called);

	// Test clear and destroy functions
	destroy_f_called = 0;
	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)43);

	vector_clear(vector);
	EXPECT_EQ(2, destroy_f_called);

	destroy_f_called = 0;
	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)43);

	vector_destroy(vector);
	EXPECT_EQ(2, destroy_f_called);

	vector = NULL;
}

TEST_F(BasicF, Insert)
{
	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)44);
	vector_push_back(&vector, (void *)45);

	ASSERT_NE(nullptr ,vector_insert(&vector, 0, (void *)41));
	ASSERT_NE(nullptr ,vector_insert(&vector, 2, (void *)43));
	ASSERT_NE(nullptr ,vector_insert(&vector, 5, (void *)46));
	ASSERT_NE(nullptr ,vector_insert(&vector, 42, (void *)47));
	ASSERT_EQ(7, vector_length(vector));
	EXPECT_EQ((void *)41, vector_get(vector, 0));
	EXPECT_EQ((void *)42, vector_get(vector, 1));
	EXPECT_EQ((void *)43, vector_get(vector, 2));
	EXPECT_EQ((void *)44, vector_get(vector, 3));
	EXPECT_EQ((void *)45, vector_get(vector, 4));
	EXPECT_EQ((void *)46, vector_get(vector, 5));
	EXPECT_EQ((void *)47, vector_get(vector, 6));
}

TEST_F(BasicF, Remove)
{
	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)43);
	vector_push_back(&vector, (void *)44);

	ASSERT_TRUE(vector_remove(vector, 1));
	ASSERT_EQ(2, vector_length(vector));
	EXPECT_EQ((void *)44, vector_get(vector, 1));

	vector_remove(vector, 1);
	ASSERT_EQ(1, vector_length(vector));
	EXPECT_EQ((void *)42, vector_get(vector, 0));
}

TEST_F(BasicF, ValidIndex)
{
	EXPECT_FALSE(vector_valid_index(vector, 0));
	EXPECT_FALSE(vector_valid_index(vector, 42));

	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)43);
	vector_push_back(&vector, (void *)44);

	EXPECT_TRUE(vector_valid_index(vector, 0));
	EXPECT_TRUE(vector_valid_index(vector, 1));
	EXPECT_TRUE(vector_valid_index(vector, 2));
	EXPECT_FALSE(vector_valid_index(vector, 3));
	EXPECT_FALSE(vector_valid_index(vector, 4));
}

TEST_F(BasicF, Truncate)
{
	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)43);
	vector_push_back(&vector, (void *)44);

	vector_truncate(vector, 42);
	ASSERT_EQ(3, vector_length(vector));

	vector_truncate(vector, 3);
	ASSERT_EQ(3, vector_length(vector));

	vector_truncate(vector, 1);
	ASSERT_EQ(1, vector_length(vector));
	EXPECT_EQ((void *)42, vector_get(vector, 0));

	vector_truncate(vector, 0);
	ASSERT_EQ(0, vector_length(vector));
}