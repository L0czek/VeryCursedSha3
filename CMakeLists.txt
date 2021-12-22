cmake_minimum_required(VERSION 3.3)

project (Keccak)
find_package(GTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(sha3
    src/multi_array.hpp
    src/template_utils.hpp
    src/sha3.hpp
    src/main.cpp)

if (GTest_FOUND)
    enable_testing()

    add_executable(sha3_test
        src/multi_array.hpp
        src/template_utils.hpp
        test/multi_array_test.cpp
        test/sha3_test.cpp)
    target_link_libraries(sha3_test
        ${GTEST_LIBRARIES}
        ${GTEST_MAIN_LIBRARIES}
        pthread
    )

    include(GoogleTest)
    gtest_discover_tests(sha3_test)
else()
    message(WARNING "GTest not found. Tests will not be built.")
endif()