#pragma once

extern "C" {
	#define  C_CONTAINER_OVERRIDE_CXX
	#include <hashmap.h>
}

#include <gtest/gtest.h>

class BasicF : public ::testing::Test {
protected:
	t_hashmap *hashmap;

	virtual void SetUp() {
		hashmap = hashmap_create();
		ASSERT_NE(hashmap, nullptr);
	}

	virtual void TearDown() {
		hashmap_destroy(hashmap);
	}
};
