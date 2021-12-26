# Function as target_sources, but using the glob expression

function(target_sources_glob target)
  cmake_parse_arguments(
    TARGET_SOURCES_GLOB
    ""
    ""
    "INTERFACE;PUBLIC;PRIVATE"
    ${ARGN})

  if(NOT TARGET_SOURCES_GLOB_INTERFACE
     AND NOT TARGET_SOURCES_GLOB_PUBLIC
     AND NOT TARGET_SOURCES_GLOB_PRIVATE)
    message(SEND_ERROR "target_sources called with incorrect number of arguments")
  endif()

  if(TARGET_SOURCES_GLOB_INTERFACE)
    foreach(glob_expression ${TARGET_SOURCES_GLOB_INTERFACE})
      file(
        GLOB_RECURSE
        src_list
        CONFIGURE_DEPENDS
        ${glob_expression})
      if(src_list)
        target_sources(${target} INTERFACE ${src_list})
      endif()
    endforeach()
  endif()

  if(TARGET_SOURCES_GLOB_PUBLIC)
    foreach(glob_expression ${TARGET_SOURCES_GLOB_PUBLIC})
      file(
        GLOB_RECURSE
        src_list
        CONFIGURE_DEPENDS
        ${glob_expression})
      if(src_list)
        target_sources(${target} PUBLIC ${src_list})
      endif()
    endforeach()
  endif()

  if(TARGET_SOURCES_GLOB_PRIVATE)
    foreach(glob_expression ${TARGET_SOURCES_GLOB_PRIVATE})
      file(
        GLOB_RECURSE
        src_list
        CONFIGURE_DEPENDS
        ${glob_expression})
      if(src_list)
        target_sources(${target} PRIVATE ${src_list})
      endif()
    endforeach()
  endif()
endfunction()
