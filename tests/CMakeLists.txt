include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(unit_tests
        stringConverter_test.cpp
        analyzer_test.cpp
        alphanumeric_test.cpp
        ErCorGenerator_test.cpp
        numeric_test.cpp
        polynomialGenerator_test.cpp
        penalty_test.cpp
        byte_test.cpp
)
target_link_libraries(unit_tests PRIVATE sut gtest_main)
include(GoogleTest)
gtest_discover_tests(unit_tests)
