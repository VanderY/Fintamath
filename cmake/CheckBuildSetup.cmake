# Check build setup

# Prevent in source builds
function(prevent_in_source_builds)
  get_filename_component(SRC_DIR ${CMAKE_SOURCE_DIR} REALPATH)
  get_filename_component(BIN_DIR ${CMAKE_BINARY_DIR} REALPATH)

  if(SRC_DIR STREQUAL BIN_DIR)
    message(
      FATAL_ERROR "In-source builds are disabled, please create a separate build directory and run cmake from there")
  endif()
endfunction()

prevent_in_source_builds()

# Check OS and compilers
function(require_minimum_compilers_version)
  set(msvc_minimum_version "19")
  set(clang_minimum_version "10")
  set(gcc_minimum_version "9")
  set(compiler_name "")
  set(compiler_version "")

  if(UNIX)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS ${gcc_minimum_version})
        set(compiler_name "GCC")
        set(compiler_version ${gcc_minimum_version})
      endif()
    elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
      if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS ${clang_minimum_version})
        set(compiler_name "Clang")
        set(compiler_version ${clang_minimum_version})
      endif()
    else()
      message(FATAL_ERROR "${CMAKE_CXX_COMPILER_ID} for ${CMAKE_SYSTEM_NAME} is not permitted, please use GCC or Clang")
    endif()
  elseif(WIN32)
    if(MSVC)
      if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS ${msvc_minimum_version})
        set(compiler_name "MVSC")
        set(compiler_version ${msvc_minimum_version})
      endif()
    else()
      message(FATAL_ERROR "${CMAKE_CXX_COMPILER_ID} for ${CMAKE_SYSTEM_NAME} is not permitted, please use MVSC")
    endif()
  else()
    message(FATAL_ERROR "${CMAKE_SYSTEM_NAME} is not permitted")
  endif()

  if(NOT
     compiler_name
     STREQUAL
     "")
    message(
      FATAL_ERROR
        "The version of ${compiler_name} is lower than required, please use ${compiler_name}-${compiler_version} or higher"
    )
  endif()
endfunction()

require_minimum_compilers_version()
