set(TEST_EXECUTABLE_NAME ${LIB_NAME}_unit_tests)

# ---[ Google Test ]------------------------

include(GoogleTest)
include(FetchContent)

FetchContent_Declare(
	googletest
	DOWNLOAD_EXTRACT_TIMESTAMP
	GIT_REPOSITORY https://github.com/google/googletest
	GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(googletest)

# ---[ Tests ]------------------------------
add_executable(
	${TEST_EXECUTABLE_NAME}
	basic.cpp
)

target_link_libraries(
	${TEST_EXECUTABLE_NAME}
	GTest::gtest_main
	${LIB_NAME}
)

# ---[ Compile options ]-------------------
target_compile_features(${TEST_EXECUTABLE_NAME} PRIVATE cxx_std_14)
target_compile_options(${TEST_EXECUTABLE_NAME} PRIVATE -g3 -fsanitize=address -Wall -Werror -Wextra)
target_link_options(${TEST_EXECUTABLE_NAME} PRIVATE -g3 -fsanitize=address)



# ---[ Setup CTest ]-----------------------
gtest_discover_tests(${TEST_EXECUTABLE_NAME} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} TEST_PREFIX "Vector/")
enable_testing()
