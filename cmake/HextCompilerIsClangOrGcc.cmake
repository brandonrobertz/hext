SET(HEXT_COMPILER_IS_CLANG_OR_GCC "FALSE")
IF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  SET(HEXT_COMPILER_IS_CLANG_OR_GCC "TRUE")
ENDIF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
