cmake_minimum_required(VERSION 3.18.0)

project(C-Containers VERSION 0.1.0)

# ---[ Options ]----------------------------
set (CMAKE_C_STANDARD 99)
set (CMAKE_C_STANDARD_REQUIRED ON)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror")

# ---[ Tests ]------------------------------

if ((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTS))
	set (VECTOR_BUILD_TESTS ON)
	enable_testing()
endif()

# ---[ Subprojects ]------------------------

add_subdirectory(vector)