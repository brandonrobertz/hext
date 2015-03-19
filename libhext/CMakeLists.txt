###### LIBHEXT #################################################################
PROJECT(libhext)

# Cmake module ExternalProject is available since 2.8.7.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7 FATAL_ERROR)

SET(
  CMAKE_MODULE_PATH
  ${PROJECT_SOURCE_DIR}/../cmake
  ${PROJECT_SOURCE_DIR}/../cmake/thirdparty)

# Force flag -std=c++11.
INCLUDE(HextForceCPP11)

# Enable all (reasonable) warnings with Clang and GCC.
INCLUDE(HextEnableWarnings)

# If build type was not specified, build Release.
INCLUDE(HextDefaultBuildRelease)

###### VERSION #################################################################
SET(PROJECT_VERSION_MAJOR 0)
SET(PROJECT_VERSION_MINOR 1)
SET(
  HEXT_VERSION_FILE_SOURCE
  "${PROJECT_SOURCE_DIR}/src/Version.cpp.in")
INCLUDE(HextGenerateVersionFile)


###### DEPENDENCIES ############################################################
FIND_PACKAGE(Boost COMPONENTS regex)
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/thirdparty)
INCLUDE(HextExternalProjectGumbo)


###### INCLUDES ################################################################
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})


###### SOURCES #################################################################
ADD_LIBRARY(
  hext
  "${PROJECT_SOURCE_DIR}/src/Builtins.cpp"
  "${PROJECT_SOURCE_DIR}/src/Hext.cpp"
  "${PROJECT_SOURCE_DIR}/src/Html.cpp"
  "${PROJECT_SOURCE_DIR}/src/NodeUtil.cpp"
  "${PROJECT_SOURCE_DIR}/src/Parser.cpp"
  "${PROJECT_SOURCE_DIR}/src/PatternBuilder.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/AttributeCapture.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/AttributeMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/BuiltinCapture.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/BuiltinMatch.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/CapturePattern.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/LiteralTest.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/MatchPattern.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/RegexTest.cpp"
  "${PROJECT_SOURCE_DIR}/src/pattern/ValueTest.cpp"
  "${PROJECT_SOURCE_DIR}/src/ResultTree.cpp"
  "${PROJECT_SOURCE_DIR}/src/RuleBuilder.cpp"
  "${PROJECT_SOURCE_DIR}/src/RulePatterns.cpp"
  "${PROJECT_SOURCE_DIR}/src/Rule.cpp"
  "${PROJECT_SOURCE_DIR}/src/StringUtil.cpp"
  "${PROJECT_SOURCE_DIR}/src/Version.cpp")
ADD_DEPENDENCIES(hext gumbo-parser)
TARGET_LINK_LIBRARIES(
  hext
  gumbo
  ${Boost_REGEX_LIBRARY})


###### INSTALL #################################################################
INSTALL(TARGETS hext DESTINATION lib)
INSTALL(DIRECTORY include/hext DESTINATION include)


###### BUILD OPTIONS ###########################################################

# Option RUNRAGEL, default OFF
# Call run_ragel.sh to generate the parser.
INCLUDE(HextOptionRunRagel)
