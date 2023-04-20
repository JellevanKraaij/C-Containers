cmake_minimum_required(VERSION 3.18.0)

project(hashmap)

# ---[ Options ]----------------------------
set(LIB_NAME hashmap)

# ---[ Create library ]---------------------
add_library(${LIB_NAME} STATIC
	src/create.c
	src/destroy.c
	src/set.c
	src/resize.c
	src/internal.c
)

# ---[ Include directories ]----------------
target_include_directories(${LIB_NAME} PUBLIC include)

# ---[ Link libraries ]---------------------
target_link_libraries(${LIB_NAME} PUBLIC vector)

# ---[ Testing] ----------------------------
if ((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTS) OR VECTOR_BUILD_TESTS)
	add_subdirectory(test)
	enable_testing()
endif()
