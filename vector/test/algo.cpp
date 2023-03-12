extern "C"
{
	#define C_CONTAINER_OVERRIDE_CXX
	#include <vector.h>
	#include <vector-algo.h>
}

#include <gtest/gtest.h>

#include "AlgoFixture.hpp"

TEST_F(AlgoF, Find)
{
	size_t index = 0;

	ASSERT_TRUE(vector_find(vector, (void *)42, &index));
	ASSERT_EQ(0, index);
	ASSERT_TRUE(vector_find(vector, (void *)43, &index));
	ASSERT_EQ(1, index);
	ASSERT_TRUE(vector_find(vector, (void *)44, &index));
	ASSERT_EQ(2, index);
	ASSERT_TRUE(vector_find(vector, (void *)45, &index));
	ASSERT_EQ(3, index);
	ASSERT_FALSE(vector_find(vector, (void *)46, &index));

	ASSERT_TRUE(vector_find(vector, (void *)43, nullptr));
	ASSERT_FALSE(vector_find(vector, (void *)46, nullptr));
}

// Inversed compare function
int cmp_fn(const void *a, const void *b, void *user_data)
{
	EXPECT_EQ((void *)42, user_data);
	if ((size_t)a == ((size_t)b - 1) )
		return 0;
	return 1;
}

TEST_F(AlgoF, CompareFN)
{
	size_t index = 0;

	vector_set_compare_fn(vector, cmp_fn, (void *)42);
	ASSERT_TRUE(vector_find(vector, (void *)43, &index));

	EXPECT_TRUE(index == 0 || index == 2);
}
