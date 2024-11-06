#include <gtest/gtest.h>
#include "pseudo.h"

using namespace pseudo;

class PseudoTest: public ::testing::Test
{
    protected:

        static void SetUpTestSuite() 
        {
            initialize();
        }

        static void TearDownTestSuite() 
        {
            // clear();
        }
};

void CHECK(Square sq, int movement, initializer_list<Square> expected)
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
    CHECK(0,   king_movement, {9, 8, 1});
    CHECK(72,  king_movement, {87, 86, 85, 73, 71, 59, 58, 57});
    CHECK(159, king_movement, {158, 151, 150});
}

TEST_F(PseudoTest, Knight)
{
    CHECK(0,   knight_movement, {17, 10});
    CHECK(72,  knight_movement, {101, 99, 88, 84, 60, 56, 45, 43});
    CHECK(159, knight_movement, {149, 142});
}

TEST_F(PseudoTest, Queen)
{
    CHECK(28, queen_movement[0], {43, 58, 73, 88, 103, 118, 133});
    CHECK(28, queen_movement[1], {42, 56, 70, 84, 98, 112, 126, 137, 145, 153});
    CHECK(28, queen_movement[2], {41, 54, 67, 80});
    CHECK(28, queen_movement[3], {29, 30, 31, 32, 33, 34, 35, 36, 37});
    CHECK(28, queen_movement[4], {27, 26, 25, 24});
    CHECK(28, queen_movement[5], {18, 11, 4});
    CHECK(28, queen_movement[6], {17, 9, 1});
    CHECK(28, queen_movement[7], {16});
}

TEST_F(PseudoTest, Rook)
{
    CHECK(100, rook_movement[0], {114, 128, 139, 147, 155});
    CHECK(100, rook_movement[1], {101, 102, 103, 104, 105, 106, 107});
    CHECK(100, rook_movement[2], {99, 98, 97, 96, 95, 94});
    CHECK(100, rook_movement[3], {86, 72, 58, 44, 30, 19, 11, 3});
}

TEST_F(PseudoTest, Bishop)
{
    CHECK(59, bishop_movement[0], {74, 89, 104, 119, 134});
    CHECK(59, bishop_movement[1], {72, 85, 98, 111, 124});
    CHECK(59, bishop_movement[2], {46, 33, 23});
    CHECK(59, bishop_movement[3], {44, 29, 17, 8});
}

TEST_F(PseudoTest, Pawn)
{
    CHECK(60, push_movement[Red],    {74});
    CHECK(60, push_movement[Blue],   {61});
    CHECK(60, push_movement[Yellow], {46});
    CHECK(60, push_movement[Green],  {59});

    CHECK(155, push_movement[Red],    {});
    CHECK(107, push_movement[Blue],   {});
    CHECK(25,  push_movement[Yellow], {});
    CHECK(136, push_movement[Green],  {});

    CHECK(60, advance_movement[Red],    {75, 73});
    CHECK(60, advance_movement[Blue],   {75, 47});
    CHECK(60, advance_movement[Yellow], {47, 45});
    CHECK(60, advance_movement[Green],  {73, 45});

    CHECK(60, attack_movement[0], {73, 45});
    CHECK(60, attack_movement[1], {75, 47});
    CHECK(60, attack_movement[2], {47, 45});
    CHECK(60, attack_movement[3], {75, 73});

    EXPECT_TRUE(IsHomerankSquare[13][Red]);
    EXPECT_TRUE(IsHomerankSquare[66][Blue]);
    EXPECT_TRUE(IsHomerankSquare[159][Yellow]);
    EXPECT_TRUE(IsHomerankSquare[50][Green]);

    EXPECT_FALSE(IsHomerankSquare[16][Red]);
    EXPECT_FALSE(IsHomerankSquare[120][Blue]);
    EXPECT_FALSE(IsHomerankSquare[30][Yellow]);
    EXPECT_FALSE(IsHomerankSquare[72][Green]);

    EXPECT_TRUE(IsPromotionSquare[130][Red]);
    EXPECT_TRUE(IsPromotionSquare[62][Blue]);
    EXPECT_TRUE(IsPromotionSquare[27][Yellow]);
    EXPECT_TRUE(IsPromotionSquare[69][Green]);

    EXPECT_FALSE(IsPromotionSquare[140][Red]);
    EXPECT_FALSE(IsPromotionSquare[80][Blue]);
    EXPECT_FALSE(IsPromotionSquare[132][Yellow]);
    EXPECT_FALSE(IsPromotionSquare[90][Green]);

    // CHECK(, , {}); // attack
}