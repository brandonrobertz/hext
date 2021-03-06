// Copyright 2015 Thomas Trapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "helper/common.h"
using namespace hext;


TEST(Pattern_ContainsTest, Succeeds)
{
  ContainsTest t("word");
  EXPECT_TRUE(t.test("word"));
  EXPECT_TRUE(t.test("words"));
  EXPECT_TRUE(t.test("sword"));
  EXPECT_TRUE(t.test("swords"));
  EXPECT_TRUE(t.test("aa words aa"));
  EXPECT_TRUE(t.test("aawordaa"));
}

TEST(Pattern_ContainsTest, Fails)
{
  ContainsTest t("word");
  EXPECT_FALSE(t.test("ward"));
  EXPECT_FALSE(t.test("sord"));
  EXPECT_FALSE(t.test("wrd"));
  EXPECT_FALSE(t.test("wor"));
  EXPECT_FALSE(t.test("nope nope nope"));
}

