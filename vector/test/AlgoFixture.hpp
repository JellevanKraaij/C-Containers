#pragma once

#include "BasicFixture.hpp"

class AlgoF : public BasicF {
protected:
	virtual void SetUp() {
		BasicF::SetUp();
		vector_push_back(&vector, (void *)42);
		vector_push_back(&vector, (void *)43);
		vector_push_back(&vector, (void *)44);
		vector_push_back(&vector, (void *)45);
	}
	virtual void TearDown() {
		BasicF::TearDown();
	}
};