# Enable compiler warnings

function(set_project_warnings project_name)
  option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

  set(msvc_warnings /W4)

  set(clang_warnings -Wall -Wpedantic -Wextra)

  if(WARNINGS_AS_ERRORS)
    set(clang_warnings ${clang_warnings} -Werror)
    set(msvc_warnings ${msvc_warnings} /WX)
  endif()

  set(gcc_warnings ${clang_warnings})

  if(MSVC)
    set(project_warnings ${msvc_warnings})
  elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(project_warnings ${clang_warnings})
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(project_warnings ${gcc_warnings})
  else()
    message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
  endif()

  target_compile_options(${project_name} INTERFACE ${project_warnings})
endfunction()
