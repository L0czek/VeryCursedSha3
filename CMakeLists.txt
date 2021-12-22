cmake_minimum_required(VERSION 3.3)

project (sha3)
find_package(GTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

set(COMMON_SOURCES
    src/template_utils.hpp
    src/multi_array.hpp
    src/bitset_rot.hpp
    src/sha3.hpp)

set(MAIN_SOURCES
    ${COMMON_SOURCES}
    src/main.cpp)

set(TEST_SOURCES
    ${COMMON_SOURCES}
    test/multi_array_test.cpp
    test/bitset_rot_test.cpp
    test/sha3_test.cpp)

add_executable(${PROJECT_NAME} ${MAIN_SOURCES})

if (GTest_FOUND)
    enable_testing()

    add_executable(${PROJECT_NAME}_test ${TEST_SOURCES})
    target_link_libraries(${PROJECT_NAME}_test
        ${GTEST_LIBRARIES}
        ${GTEST_MAIN_LIBRARIES}
        pthread
    )

    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}_test)
else()
    message(WARNING "GTest not found. Tests will not be built.")
endif()