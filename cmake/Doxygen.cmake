# Enable doxygen

option(ENABLE_DOXYGEN "Enable doxygen doc builds of source" OFF)
if(NOT ENABLE_DOXYGEN)
  return()
endif()

function(enable_doxygen)
  set(DOXYGEN_CALLER_GRAPH YES)
  set(DOXYGEN_CALL_GRAPH YES)
  set(DOXYGEN_EXTRACT_ALL YES)
  find_package(Doxygen REQUIRED dot)
  doxygen_add_docs(doxygen-docs ${PROJECT_SOURCE_DIR})
endfunction()

enable_doxygen()
