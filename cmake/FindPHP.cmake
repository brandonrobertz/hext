# http://www.cmake.org/cmake/help/v3.0/module/FindPackageHandleStandardArgs.html

# Find PHP using php-config.
# Sets PHP_INCLUDE_DIRS if successful.

INCLUDE(CMakeFindFrameworks)
INCLUDE(FindPackageHandleStandardArgs)

FIND_PROGRAM(PHP_CONFIG NAMES "php-config" "php-config5")

IF(PHP_CONFIG)
  EXECUTE_PROCESS(
    COMMAND ${PHP_CONFIG} "--includes"
    OUTPUT_VARIABLE PHP_INCLUDE_DIRS)
  STRING(REPLACE "\n" "" PHP_INCLUDE_DIRS "${PHP_INCLUDE_DIRS}")
  STRING(REPLACE "-I" ";" PHP_INCLUDE_DIRS "${PHP_INCLUDE_DIRS}")
ENDIF(PHP_CONFIG)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Php DEFAULT_MSG PHP_INCLUDE_DIRS)

