#include <gtest/gtest.h>
#include "definitions.h"

using namespace definitions;

class DefinitionsTest: public ::testing::Test
{
    protected:

};

TEST_F(DefinitionsTest, RankMacro)
{
    EXPECT_EQ(Rank(0), 0);
    EXPECT_EQ(Rank(10), 1);
    EXPECT_EQ(Rank(60), 5);
    EXPECT_EQ(Rank(140), 11);
    EXPECT_EQ(Rank(159), 13);
}

TEST_F(DefinitionsTest, FileMacro)
{
    EXPECT_EQ(File(0), 3);
    EXPECT_EQ(File(10), 5);
    EXPECT_EQ(File(60), 8);
    EXPECT_EQ(File(140), 7);
    EXPECT_EQ(File(159), 10);
}

TEST_F(DefinitionsTest, SpotMacro)
{
    EXPECT_EQ(Spot(0, 3), 0);
    EXPECT_EQ(Spot(1, 5), 10);
    EXPECT_EQ(Spot(5, 8), 60);
    EXPECT_EQ(Spot(11, 7), 140);
    EXPECT_EQ(Spot(13, 10), 159);
}