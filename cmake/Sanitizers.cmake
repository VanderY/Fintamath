# Enable sanitizers

function(enable_sanitizers project_name)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(ENABLE_SANITIZERS "Enable sanitizers" OFF)
    if(ENABLE_SANITIZERS)
      set(sanitizers "address,undefined")
      target_compile_options(${project_name} INTERFACE -fsanitize=${sanitizers})
      target_link_options(${project_name} INTERFACE -fsanitize=${sanitizers})
    endif()
  endif()
endfunction()
