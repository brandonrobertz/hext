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


TEST(Pattern_EndsWithTest, Succeeds)
{
  EndsWithTest t("word");
  EXPECT_TRUE(t.test("word"));
  EXPECT_TRUE(t.test("sword"));
  EXPECT_TRUE(t.test(" word"));
  EXPECT_TRUE(t.test("wordwordword"));
  EXPECT_TRUE(t.test("word word word"));
}

TEST(Pattern_EndsWithTest, Fails)
{
  EndsWithTest t("word");
  EXPECT_FALSE(t.test("words"));
  EXPECT_FALSE(t.test("swor"));
  EXPECT_FALSE(t.test("wrd"));
  EXPECT_FALSE(t.test("wordwor"));
}

