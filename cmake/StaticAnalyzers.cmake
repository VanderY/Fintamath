# Enable static analyzers

option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
if(ENABLE_CPPCHECK)
  find_program(CPPCHECK_BINARY cppcheck)
  if(CPPCHECK_BINARY)
    set(CMAKE_CXX_CPPCHECK
        ${CPPCHECK_BINARY}
        --suppress=missingInclude
        --suppress=unmatchedSuppression
        --enable=all
        --inline-suppr
        --inconclusive)
  else()
    message(SEND_ERROR "cppcheck requested but executable not found")
  endif()
endif()

option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)
if(ENABLE_CLANG_TIDY)
  find_program(CLANGTIDY_BINARY clang-tidy)
  if(CLANGTIDY_BINARY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY_BINARY} -extra-arg=-Wno-unknown-warning-option)
  else()
    message(SEND_ERROR "clang-tidy requested but executable not found")
  endif()
endif()

option(ENABLE_INCLUDE_WHAT_YOU_USE "Enable static analysis with include-what-you-use" OFF)
if(ENABLE_INCLUDE_WHAT_YOU_USE)
  find_program(IWYU_BINARY include-what-you-use)
  if(IWYU_BINARY)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU_BINARY})
  else()
    message(SEND_ERROR "include-what-you-use requested but executable not found")
  endif()
endif()
