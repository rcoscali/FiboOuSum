cmake_minimum_required(VERSION 3.10)
project(Fibo C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
# the test suite will require C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include directory for headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# library containing the core functions
add_library(fibosum STATIC src/lib.c)

target_include_directories(fibosum PUBLIC ${PROJECT_SOURCE_DIR}/include)

# main executable (renamed)
add_executable(SumOuFibo src/main.c)
target_link_libraries(SumOuFibo fibosum)

# unit tests
# rely on installed Google Test; users should install the package (e.g. libgtest-dev on Debian/Ubuntu)
find_package(GTest REQUIRED)
enable_testing()
add_executable(test_sum tests/test_sum.cpp)
target_link_libraries(test_sum
    GTest::gtest_main
    fibosum
)

include(GoogleTest)
gtest_discover_tests(test_sum)
