#include <gtest/gtest.h>
#include "pseudo.h"

using namespace pseudo;

class PseudoTest: public ::testing::Test
{
    protected:

        Square sq;

        vector<Square> expected;

        unsigned int idx = 0;

        static void SetUpTestSuite() 
        {
            initialize();
        }

        static void TearDownTestSuite() 
        {
            // clear();
        }
};

void check(Square sq, int movement, initializer_list<Square> expected)
{
    EXPECT_EQ(range[sq][movement], expected.size());

    int i = 0;
    for (Square target: expected)
    {
        EXPECT_EQ(squares[start[sq][movement] + i++], target);
    }
}

TEST_F(PseudoTest, King)
{
    check(0,   KING_MOVEMENT, {9, 8, 1});
    check(72,  KING_MOVEMENT, {87, 86, 85, 73, 71, 59, 58, 57});
    check(159, KING_MOVEMENT, {158,151,150});
}

TEST_F(PseudoTest, Knight)
{
    check(0,   KNIGHT_MOVEMENT, {17, 10});
    check(72,  KNIGHT_MOVEMENT, {101, 99, 88, 84, 60, 56, 45, 43});
    check(159, KNIGHT_MOVEMENT, {149, 142});
}

/*
TEST_F(PseudoTest, Slide)
{
    pseudo.init(config);

    EXPECT_EQ(pseudo.slide[28][0], vector<Square>({43, 58, 73, 88, 103, 118, 133}));
    EXPECT_EQ(pseudo.slide[28][1], vector<Square>({42, 56, 70, 84, 98, 112, 126, 137, 145, 153}));
    EXPECT_EQ(pseudo.slide[28][2], vector<Square>({41, 54, 67, 80}));
    EXPECT_EQ(pseudo.slide[28][3], vector<Square>({29, 30, 31, 32, 33, 34, 35, 36, 37}));
    EXPECT_EQ(pseudo.slide[28][4], vector<Square>({27, 26, 25, 24}));
    EXPECT_EQ(pseudo.slide[28][5], vector<Square>({18, 11, 4}));
    EXPECT_EQ(pseudo.slide[28][6], vector<Square>({17, 9, 1}));
    EXPECT_EQ(pseudo.slide[28][7], vector<Square>({16}));
}
*/