# numbers library

add_library(numbers)
add_library(${PROJECT_NAME}::numbers ALIAS numbers)

target_sources_glob(
  numbers
  PUBLIC "include/*.hpp"
  PRIVATE "src/*.cpp")

target_include_directories(numbers PUBLIC include)

target_link_libraries(
  numbers
  PUBLIC ${PROJECT_NAME}::math_abstractions
  PRIVATE ${PROJECT_NAME}::project_dependencies)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
