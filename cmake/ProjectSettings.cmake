# Project settings

# Set build type
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE
      RelWithDebInfo
      CACHE STRING "Choose the type of build." FORCE)
  set_property(
    CACHE CMAKE_BUILD_TYPE
    PROPERTY STRINGS
             "Debug"
             "Release"
             "MinSizeRel"
             "RelWithDebInfo")
endif()

# Enable testing
option(BUILD_TESTS "Enable Test Builds" ON)
if(BUILD_TESTS)
  enable_testing()
  message("Building tests")
endif()

# Export compiler commands to compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build all libraries as shared unless the library was explicitly added as a static library
option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)

# OS specific options
if(APPLE)
  set(CMAKE_MACOSX_RPATH OFF)
elseif(WIN32)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()
