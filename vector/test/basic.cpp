extern "C" {
	#define VECTOR_OVERRIDE_CXX
	#include <vector.h>
}

#include <gtest/gtest.h>
#include "BasicFixture.hpp"

TEST(Basic, createAndDestroy) {
	t_vector *vector = vector_create();
	ASSERT_NE(nullptr, vector);
	vector_destroy(vector);
}

TEST_F(BasicF, Resize) {
	vector_reserve(&vector, 10);
	ASSERT_GE(vector_capacity(vector), 10);	
}

TEST_F(BasicF, PushBack) {
	ASSERT_NE(nullptr, vector_push_back(&vector, (void *)42));
	ASSERT_NE(nullptr, vector_push_back(&vector, (void *)43));
	ASSERT_EQ(2, vector_length(vector));
	EXPECT_EQ((void *)42, vector_get(vector, 0));
	EXPECT_EQ((void *)43, vector_get(vector, 1));
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

TEST_F(BasicF, PushFront)
{
	ASSERT_TRUE(vector_push_front(&vector, (void *)42));
	ASSERT_TRUE(vector_push_front(&vector, (void *)43));
	ASSERT_EQ(2, vector_length(vector));
	EXPECT_EQ((void *)43, vector_get(vector, 0));
	EXPECT_EQ((void *)42, vector_get(vector, 1));
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

//TODO: Implement Destroy Function test

// TEST_F(BasicF, DestroyFunction)
// {
// 	vector_push_back(&vector, (void *)42);
// 	vector_push_back(&vector, (void *)43);
// 	ASSERT_EQ(2, vector_length(vector));
// 	vector_set_destroy_f(vector, {[](void *data) {  }});
// 	ASSERT_EQ(0, *(int *)vector_get(vector, 0));
// 	ASSERT_EQ(0, *(int *)vector_get(vector, 1));
// }