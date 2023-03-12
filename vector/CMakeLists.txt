cmake_minimum_required(VERSION 3.18.0)

project(vector)

# ---[ Options ]----------------------------
set(LIB_NAME vector)

# ---[ Create library ]---------------------
add_library(${LIB_NAME} STATIC
	src/clear.c
	src/create.c
	src/destroy.c
	src/get.c
	src/insert.c
	src/pop.c
	src/push.c
	src/remove.c
	src/resize.c
	src/set.c
	src/stats.c
	src/algo/find.c
)

# ---[ Include directories ]----------------
target_include_directories(${LIB_NAME} PUBLIC include)

# ---[ Testing] ----------------------------
if ((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTS) OR VECTOR_BUILD_TESTS)
	add_subdirectory(test)
	enable_testing()
endif()
