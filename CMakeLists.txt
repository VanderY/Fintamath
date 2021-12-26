cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Project details
project(
  fintamath
  VERSION 0.1
  LANGUAGES C CXX)

# Project settings
include(cmake/CheckBuildSetup.cmake)
include(cmake/ProjectSettings.cmake)

# Enable Interprocedural Optimization
include(cmake/IPO.cmake)

# Add the project_dependencies library
add_library(project_dependencies INTERFACE)
add_library(${PROJECT_NAME}::project_dependencies ALIAS project_dependencies)

# Set the C++ standard
target_compile_features(project_dependencies INTERFACE cxx_std_17)

# Enable cache system
include(cmake/Cache.cmake)

# Standard compiler warnings
include(cmake/ProjectWarnings.cmake)
set_project_warnings(project_dependencies)

# Enable sanitizers
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_dependencies)

# Enable coverage
include(cmake/Coverage.cmake)
enable_coverage(project_dependencies)

# Enable doxygen
include(cmake/Doxygen.cmake)

# Enable static analyzers
include(cmake/StaticAnalyzers.cmake)

# Provide target_sources_glob function
include(${CMAKE_SOURCE_DIR}/cmake/TargetSourcesGlob.cmake)

# Add subdirectories
add_subdirectory(third_party)
add_subdirectory(src)
