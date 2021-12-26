# terms library

add_subdirectory(numbers)

add_library(terms)
add_library(${PROJECT_NAME}::terms ALIAS terms)

target_sources_glob(
  terms
  PUBLIC "include/*.hpp"
  PRIVATE "src/*.cpp")

target_include_directories(terms PUBLIC include)

target_link_libraries(
  terms
  PUBLIC ${PROJECT_NAME}::math_abstractions ${PROJECT_NAME}::numbers
  PRIVATE ${PROJECT_NAME}::project_dependencies)
