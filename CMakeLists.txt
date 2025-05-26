cmake_minimum_required(VERSION 3.10.0)
project(fst VERSION 0.1.0 LANGUAGES C CXX)

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
enable_testing()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
  if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
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

FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

include_directories(include)
set(SRC
    src/main.cpp
    src/logger.cpp
)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

add_executable(hello_test tests/test.cpp)
target_link_libraries(hello_test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(hello_test)
