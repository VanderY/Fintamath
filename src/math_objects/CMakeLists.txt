# math_objects library

add_subdirectory(math_abstractions)
add_subdirectory(nodes)

add_library(math_objects)
add_library(${PROJECT_NAME}::math_objects ALIAS math_objects)

target_sources_glob(
  math_objects
  PUBLIC "include/*.hpp"
  PRIVATE "src/*.cpp")

target_include_directories(math_objects PUBLIC include)

target_link_libraries(
  math_objects
  PUBLIC ${PROJECT_NAME}::math_abstractions ${PROJECT_NAME}::nodes
  PRIVATE ${PROJECT_NAME}::project_dependencies)
