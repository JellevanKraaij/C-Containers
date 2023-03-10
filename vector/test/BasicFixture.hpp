#pragma once

extern "C" {
	#define C_CONTAINER_OVERRIDE_CXX
	#include <vector.h>
}

#include <gtest/gtest.h>

class BasicF : public ::testing::Test {
protected:
	t_vector *vector;

	virtual void SetUp() {
		vector = vector_create();
		ASSERT_NE(vector, nullptr);
	}

	virtual void TearDown() {
		vector_destroy(vector);
	}
};
