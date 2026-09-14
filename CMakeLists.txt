cmake_minimum_required(VERSION 3.25)

project(Athena LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Git QUIET)

set(ATHENA_VERSION "unknown")

if(GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --tags --always --dirty
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE ATHENA_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
        RESULT_VARIABLE GIT_RESULT
        ERROR_QUIET
    )

    if(NOT GIT_RESULT EQUAL 0 OR ATHENA_VERSION STREQUAL "")
        set(ATHENA_VERSION "unknown")
    endif()
endif()

file(GLOB_RECURSE ATHENA_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_library(athena_lib STATIC
    ${ATHENA_SOURCES}
)

target_compile_features(athena_lib PUBLIC 
    cxx_std_23
)

target_include_directories(athena_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

target_compile_definitions(athena_lib PRIVATE
    ATHENA_VERSION="${ATHENA_VERSION}"
)

target_compile_options(athena_lib PUBLIC
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Release>:-march=native>
)

add_executable(athena
    src/main.cc
)

target_link_libraries(athena PRIVATE
    athena_lib
)

include(CheckIPOSupported)

check_ipo_supported(
    RESULT ipo_supported
    OUTPUT ipo_error
)

if(ipo_supported)
    set_target_properties(athena_lib athena PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION
        $<$<CONFIG:Release>:TRUE>
    )
endif()

include(FetchContent)

FetchContent_Declare(benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG        v1.9.1
    GIT_SHALLOW    ON
    SYSTEM
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(benchmark)

add_executable(perft_bench bench/perft_bench.cc)

target_link_libraries(perft_bench PRIVATE
    athena_lib
    benchmark::benchmark_main
)

if(ipo_supported)
    set_target_properties(perft_bench PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION $<$<CONFIG:Release>:TRUE>)
endif()

enable_testing()

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
    GIT_SHALLOW    ON
    SYSTEM
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(perft_test tests/perft_test.cc)
target_link_libraries(perft_test PRIVATE
    athena_lib
    GTest::gtest_main
)
target_compile_definitions(perft_test PRIVATE
    PERFT_DATA_DIR="${CMAKE_SOURCE_DIR}/tests/data")

add_executable(nnue_test tests/nnue_test.cc)
target_link_libraries(nnue_test PRIVATE
    athena_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(perft_test
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    PROPERTIES TIMEOUT 120
)
gtest_discover_tests(nnue_test
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# # ---------------- Compiler options ----------------
# add_library(athena_options INTERFACE)
# target_compile_features(athena_options INTERFACE cxx_std_23)
# target_compile_options(athena_options INTERFACE -Wall -Wextra -Wpedantic -Wshadow)

# if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#     target_compile_options(athena_options INTERFACE
#         $<$<CONFIG:Release>:-O3 -march=native>)
# elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#     target_compile_options(athena_options INTERFACE /W4
#         $<$<CONFIG:Release>:/O2 /arch:AVX2>)
# endif()

# # ---------------- IPO / LTO ----------------
# include(CheckIPOSupported)
# check_ipo_supported(RESULT ipo_supported OUTPUT ipo_error)
# if(NOT ipo_supported)
#     message(STATUS "IPO/LTO not supported: ${ipo_error}")
# endif()

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# # add_subdirectory(src)

# file(GLOB_RECURSE ATHENA_SRC CONFIGURE_DEPENDS
#     chess/*.cpp
#     nnue/*.cpp
#     uci/*.cpp
#     *.cpp
# )
# list(REMOVE_ITEM ATHENA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/athena.cc)

# add_library(athena_lib STATIC ${ATHENA_SRC})
# target_include_directories(athena_lib PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${CMAKE_BINARY_DIR}   # for generated misc.h
# )
# target_link_libraries(athena_lib PUBLIC athena_options)

# if(ipo_supported)
#     set_target_properties(athena_lib PROPERTIES
#         INTERPROCEDURAL_OPTIMIZATION $<$<CONFIG:Release>:TRUE>)
# endif()

# add_executable(athena athena.cc)
# target_link_libraries(athena PRIVATE athena_lib)

# if(ipo_supported)
#     set_target_properties(athena PROPERTIES
#         INTERPROCEDURAL_OPTIMIZATION $<$<CONFIG:Release>:TRUE>)
# endif()


# # Get version from git
# find_package(Git QUIET)

# set(ATHENA_VERSION "unknown")

# if(GIT_FOUND)
#     execute_process(
#         COMMAND ${GIT_EXECUTABLE} describe --tags --dirty --always
#         WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#         OUTPUT_VARIABLE ATHENA_VERSION
#         OUTPUT_STRIP_TRAILING_WHITESPACE
#         ERROR_QUIET
#     )
# endif()

# # Fallback if git failed
# if(NOT ATHENA_VERSION)
#     set(ATHENA_VERSION "dev")
# endif()

# message(STATUS "Athena version: ${ATHENA_VERSION}")

# # Pass it to the compiler
# target_compile_definitions(athena PRIVATE ATHENA_VERSION="${ATHENA_VERSION}")

# ---------------- Tests ----------------
# enable_testing()
# add_subdirectory(tests)

# include(FetchContent)

# # -------------------------
# # GoogleTest
# # -------------------------
# FetchContent_Declare(googletest
#     GIT_REPOSITORY https://github.com/google/googletest.git
#     GIT_TAG        v1.15.2
#     GIT_SHALLOW    ON
#     GIT_PROGRESS   ON
#     SYSTEM
#     FIND_PACKAGE_ARGS NAMES GTest
# )
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

# # -------------------------
# # Google Benchmark
# # -------------------------
# FetchContent_Declare(benchmark
#     GIT_REPOSITORY https://github.com/google/benchmark.git
#     GIT_TAG        v1.9.1
#     GIT_SHALLOW    ON
#     GIT_PROGRESS   ON
#     SYSTEM
# )
# set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
# set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(benchmark)

# # -------------------------
# # Test data path
# # -------------------------
# set(PERFT_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data")

# # -------------------------
# # Unit tests
# # -------------------------
# add_executable(perft_test perft_test.cc)
# target_link_libraries(perft_test PRIVATE
#     athena_lib
#     GTest::gtest_main
#     athena_options)
# target_compile_definitions(perft_test PRIVATE
#     PERFT_DATA_DIR="${PERFT_DATA_DIR}")

# include(GoogleTest)
# gtest_discover_tests(perft_test
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#     PROPERTIES TIMEOUT 120
# )

# # -------------------------
# # Benchmarks
# # -------------------------
# add_executable(perft_bench perft_bench.cc)
# target_link_libraries(perft_bench PRIVATE
#     athena_lib
#     benchmark::benchmark_main
#     athena_options)