cmake_minimum_required(VERSION 3.27)
project(assignment_4_1)

set(CMAKE_CXX_STANDARD 17)

find_package(cpprestsdk REQUIRED)

add_executable(assignment_4_1 main.cpp)

target_link_libraries(assignment_4_1 PRIVATE cpprestsdk::cpprest)

if (UNIX)
    target_link_libraries(assignment_4_1 PRIVATE crypto)
endif (UNIX)

if (APPLE)
    set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl@1.1)
    include_directories(/opt/homebrew/opt/openssl@1.1/include)
    link_directories(/opt/homebrew/opt/openssl@1.1/lib)
    target_link_libraries(assignment_4_1 PRIVATE cpprestsdk::cpprest)
endif (APPLE)



