#include <gtest/gtest.h>
#include "definitions.h"

using namespace definitions;

class DefinitionsTest: public ::testing::Test
{
    protected:

};

TEST_F(DefinitionsTest, RankMacro)
{
    EXPECT_EQ(Rank(10), 1);
}

TEST_F(DefinitionsTest, FileMacro)
{
    EXPECT_EQ(File(10), 5);
}

TEST_F(DefinitionsTest, SpotMacro)
{
    EXPECT_EQ(Spot(1, 5), 10);
}