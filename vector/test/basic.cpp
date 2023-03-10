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
	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)43);
	ASSERT_NE(nullptr, vector_pop_back(&vector, NULL));
	EXPECT_EQ(1, vector_length(vector));

	void *data = NULL;
	ASSERT_NE(nullptr, vector_pop_back(&vector, &data));
	ASSERT_EQ(0, vector_length(vector));
	EXPECT_EQ((void *)42, data);
}

TEST_F(BasicF, PushFront)
{
	ASSERT_NE(nullptr, vector_push_front(&vector, (void *)42));
	ASSERT_NE(nullptr, vector_push_front(&vector, (void *)43));
	ASSERT_EQ(2, vector_length(vector));
	EXPECT_EQ((void *)43, vector_get(vector, 0));
	EXPECT_EQ((void *)42, vector_get(vector, 1));
}

TEST_F(BasicF, PopFront)
{
	vector_push_front(&vector, (void *)42);
	vector_push_front(&vector, (void *)43);
	ASSERT_NE(nullptr, vector_pop_front(&vector, NULL));
	EXPECT_EQ(1, vector_length(vector));

	void *data = NULL;
	ASSERT_NE(nullptr, vector_pop_front(&vector, &data));
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

	void *data = NULL;
	ASSERT_NE(nullptr, vector_at(vector, 0, &data));
	EXPECT_EQ((void *)42, data);
	ASSERT_NE(nullptr, vector_at(vector, 1, &data));
	EXPECT_EQ((void *)43, data);
}

TEST_F(BasicF, AtFail)
{
	EXPECT_EQ(nullptr, vector_at(vector, 0, NULL));

	vector_push_back(&vector, (void *)42);
	vector_push_back(&vector, (void *)43);

	void *data = NULL;
	EXPECT_EQ(nullptr, vector_at(vector, 2, &data));
	EXPECT_EQ(nullptr, vector_at(vector, 3, &data));
	EXPECT_EQ(nullptr, data);
}
