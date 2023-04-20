extern "C" {
	#define C_CONTAINER_OVERRIDE_CXX
	#include <vector.h>
}

#include <gtest/gtest.h>
#include "BasicFixture.hpp"

TEST(Basic, CreateAndDestroy) {
	t_hashmap *hashmap = hashmap_create();
	ASSERT_NE(hashmap, nullptr);
	hashmap_destroy(hashmap);

	hashmap = hashmap_create();
	ASSERT_NE(hashmap, nullptr);
	hashmap_destroy_null(&hashmap);
	ASSERT_EQ(hashmap, nullptr);
}
