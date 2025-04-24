cmake_minimum_required(VERSION 3.28)
project(run_tests)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(run_tests
        tests.cpp
        ../processing_server/ProcessingServer.cpp
        ../socket/Socket.cpp
        main.cpp
)



target_link_libraries(run_tests
        ${GTEST_LIBRARIES}
        pthread
)