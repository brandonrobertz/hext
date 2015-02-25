#include "gtest/gtest.h"

#include "string-util/main.h"
#include "builtins/main.h"
#include "file/main.h"


int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

