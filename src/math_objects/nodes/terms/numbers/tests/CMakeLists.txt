# numbers_tests executable

add_executable(numbers_tests)

target_sources_glob(numbers_tests PRIVATE "*.cpp")

target_link_libraries(numbers_tests PRIVATE ${PROJECT_NAME}::numbers ${PROJECT_NAME}::project_dependencies
                                            GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(numbers_tests)
