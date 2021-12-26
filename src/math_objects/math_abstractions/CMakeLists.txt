# math_abstractions library

add_library(math_abstractions INTERFACE)
add_library(${PROJECT_NAME}::math_abstractions ALIAS math_abstractions)

target_sources_glob(math_abstractions INTERFACE "include/*.hpp")

target_include_directories(math_abstractions INTERFACE include)
