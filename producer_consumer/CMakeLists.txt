cmake_minimum_required(VERSION 3.0.0)
project(mul_producer_single_consumer VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(mul_producer_single_consumer 多生产单消费.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
