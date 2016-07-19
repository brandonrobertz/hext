INCLUDE(CheckCXXCompilerFlag)
IF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CPP14)
  IF(COMPILER_SUPPORTS_CPP14)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  ELSE(COMPILER_SUPPORTS_CPP14)
    MESSAGE(SEND_ERROR "${CMAKE_CXX_COMPILER} does not support the flag -std=c++14.")
    MESSAGE(FATAL_ERROR "C++14 is required.")
  ENDIF(COMPILER_SUPPORTS_CPP14)
ENDIF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

