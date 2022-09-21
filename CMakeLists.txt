cmake_minimum_required(VERSION 3.15.0)
project(ilp_issue_repro VERSION 2.0.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
        c-questdb-client
        GIT_REPOSITORY https://github.com/questdb/c-questdb-client.git
        GIT_TAG origin/main)
FetchContent_MakeAvailable(c-questdb-client)

add_executable(
    main
    main.cpp)
target_link_libraries(
    main
    questdb_client)