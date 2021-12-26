# nodes library

add_subdirectory(terms)

add_library(nodes)
add_library(${PROJECT_NAME}::nodes ALIAS nodes)

target_sources_glob(
  nodes
  PUBLIC "include/*.hpp"
  PRIVATE "src/*.cpp")

target_include_directories(nodes PUBLIC include)

target_link_libraries(
  nodes
  PUBLIC ${PROJECT_NAME}::math_abstractions ${PROJECT_NAME}::terms
  PRIVATE ${PROJECT_NAME}::project_dependencies)
