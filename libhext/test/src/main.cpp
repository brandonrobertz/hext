#include "gtest/gtest.h"

#include "string-util/main.h"
#include "builtins/main.h"
#include "node-util/main.h"
#include "parser/main.h"
#include "pattern/attribute-capture.h"
#include "pattern/attribute-match.h"


int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

