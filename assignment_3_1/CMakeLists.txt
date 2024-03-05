cmake_minimum_required(VERSION 3.26)
project(assignment_3_1)

set(CMAKE_CXX_STANDARD 14)

add_library(sqlite3 sqlite3/sqlite3.c)
target_include_directories(sqlite3 PUBLIC sqlite3)

if (UNIX)
    target_link_libraries(sqlite3 pthread dl)
endif (UNIX)

add_library(sqlitecpp
sqlitecpp/src/Backup.cpp
sqlitecpp/src/Column.cpp
sqlitecpp/src/Database.cpp
sqlitecpp/src/Exception.cpp
sqlitecpp/src/Statement.cpp
sqlitecpp/src/Transaction.cpp)

target_include_directories(sqlitecpp PUBLIC sqlitecpp/include)
target_link_libraries(sqlitecpp sqlite3)

add_executable(assignment_3_1 main.cpp)
target_include_directories(assignment_3_1 PUBLIC .)
target_link_libraries(assignment_3_1 sqlite3 sqlitecpp)