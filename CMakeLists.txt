cmake_minimum_required(VERSION 3.10.0)
project(fst VERSION 0.1.5 LANGUAGES C CXX)

option(CODE_COVERAGE "Enable coverage reporting" OFF)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
if(WIN32)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
  bs_thread_pool
  URL https://github.com/bshoshany/thread-pool/archive/refs/tags/v4.1.0.zip
)
FetchContent_MakeAvailable(bs_thread_pool)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
  if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
  endif()

  if(CODE_COVERAGE)
    message(STATUS "Code coverage enabled")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
  endif()

  add_compile_options(
    -Wall
    -Wextra
    -Wconversion
    -Wsign-conversion
    -Wshadow
    -Wduplicated-cond
    -Wnull-dereference
    -Wdouble-promotion
    -Wformat=2
  )
endif()

get_filename_component(PROJECT_ROOT "${CMAKE_SOURCE_DIR}" ABSOLUTE)
string(REPLACE "\\" "/" PROJECT_ROOT "${PROJECT_ROOT}")
string(LENGTH "${PROJECT_ROOT}" PROJECT_ROOT_LEN)
math(EXPR PROJECT_ROOT_END "${PROJECT_ROOT_LEN} - 1")
string(SUBSTRING "${PROJECT_ROOT}" ${PROJECT_ROOT_END} 1 PROJECT_ROOT_LAST_CHAR)
if(NOT PROJECT_ROOT_LAST_CHAR STREQUAL "/")
    set(PROJECT_ROOT "${PROJECT_ROOT}/")
endif()
add_compile_definitions(PROJECT_ROOT="${PROJECT_ROOT}")

include_directories(include)
set(FST_LIB_SRC
    src/logger.cpp
    src/word_iter.cpp
    src/inverted_index.cpp
    src/config.cpp
    src/answers.cpp
    src/search_server.cpp
    src/request.cpp
)
add_library(FST_LIB STATIC ${FST_LIB_SRC})
target_link_libraries(FST_LIB nlohmann_json::nlohmann_json)
target_include_directories(FST_LIB PRIVATE ${bs_thread_pool_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} src/main.cpp ${LIB_SRC})
target_link_libraries(${PROJECT_NAME} FST_LIB)

enable_testing()
include(GoogleTest)

add_executable(test_word_iter tests/test_word_iter.cpp ${LIB_SRC})
target_link_libraries(test_word_iter PRIVATE GTest::gtest_main FST_LIB)
gtest_discover_tests(test_word_iter)

add_executable(test_inverted_index tests/test_inverted_index.cpp ${LIB_SRC})
target_link_libraries(test_inverted_index PRIVATE GTest::gtest_main FST_LIB)
gtest_discover_tests(test_inverted_index)

add_executable(test_answers tests/test_answers.cpp ${LIB_SRC})
target_link_libraries(test_answers PRIVATE GTest::gtest_main FST_LIB)
gtest_discover_tests(test_answers)

add_executable(test_search_server tests/test_search_server.cpp ${LIB_SRC})
target_link_libraries(test_search_server PRIVATE GTest::gtest_main FST_LIB)
gtest_discover_tests(test_search_server)
